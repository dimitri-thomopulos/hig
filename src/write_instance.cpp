/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*        ,/      ___      ___                                               */
/*      ,'/      /__/|    /__/|   ___      ___     __________      ________  */
/*    ,' /      |  | |   |  | |  /__/|    /__/|   /_________/\    /_______/\ */
/*  ,'  /_____, |  | |___|  | | |  | |   |  |'|  /    __   `\`\  |   ___ `\/|*/
/*.'____    ,'  |  |/____|  | | |  | |   |  | | |   /|   \___|/' |  | |_\ | |*/
/*     /  ,'    |   _____   | | |  | |   |  | | |  | |     ___   |  |/__/ |/'*/
/*    / ,'      |  | |   |  | | |  | `\_/|  |`| |  | `\__//__/|` |   _____/' */
/*   /,'        |  | |   |  | | |   \`__/   |/' |   \`___/   |/  |  | /`     */
/*  /'          |  |/'   |  |/'  \          //'  \          //'  |  |/'      */
/*              `~~'     `~~''     `~~~~~~~''      `~~~~~~~~''   `~~''       */
/*                                                                           */
/*    __________                                                       ,/    */
/*   /_________/\                                                    ,'/     */
/*  /    __   `\`\       ________       ___       ___              ,' /      */
/* |   /|   \___|/'     /________/|    /___/\   /___/|           ,'  /_____, */
/* |  | |    ______    |   _____|/'   |   \   \|   | |         .'____    ,'  */
/* |  | |   /_____/|   |  |___/|      |     \  |   | |              /  ,'    */
/* |  | `\_|_   _|/    |   __|/'__    |   |\  \|   | |    ___      / ,'      */
/* |   \`____|' |/'    |  |_____ /|   |   | |\     | |   /__/|    /,'        */
/*  \          //'     |        |/'   |   |/'  \   |/'  |  |/'   /'          */
/*   `~~~~~~~~''       `~~~~~~~''     `~~~'     `~~~''  `~~''                */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* @file     :write_instance.cpp
 * @brief    :Functions for writing the instances
 * @author   :Dimitri Thomopulos
 * @date     :20180730
 * @version  :1.01
 */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "write_instance.h"

using namespace std;

string monthNames[12] = { "January", "February", "March", "April", "May", 
"June", "July", "August", "September", "October", "November", "December" };

double const coeff_eta[7] = { 4.09863600116008, -1.25535942295343, 
0.160530264942775, -0.00976201903589132, 0.000309429429972963,
-4.92928898248035E-06, 0.0000000311519548768 };

double const min_jump = 71.50;
double const max_jump = 85.25;

int print_perc(double *linesCount, double linesStep, int linesAdded){ 
	(*linesCount) += linesAdded;
	while ((*linesCount)>linesStep){
		cout << "=";
		(*linesCount) -= linesStep;
	}
	return 0;
}

//function to create three digits numbers
string three_digits_string(int threeValue){
	stringstream ss;
	ss << (threeValue + 1000);
	string str = ss.str();
	string threeDigits = str.substr(1, 4);
	return threeDigits;
}


int write_instance(int instFormat, int year, int month, int day,
	int periodsNumber, int nOPT, double **prices, double **inflows, int RVol,
	int v_0_modif, int v_T_modif, int v_min_modif, int v_max_modif){
	stringstream sStream; //string to create the name of the file
	string instFolder; //path/name of the folder of instances
	int origPrecision; //variable to memorize the original output precision
	double linesCount = 0.0001; //counter of printed lines
	double linesStep = 0.0001; //number of lines to print a percentage after
	int verbose = 1; // 1 to print percentage of done lines, 0 otherwise

	int v_min = v_LB + (v_min_modif * v_step);
	int v_max = v_UB - (v_min_modif * v_step);
	int v_0 = v_LB + (v_0_modif * v_double_step);
	int v_T = v_LB + (v_T_modif * v_double_step);

	//Creating instances folders
	switch (instFormat)
	{
	case 0:
		instFolder = "Single-reservoir_instances";
		system("mkdir Single-reservoir_instances");
		linesStep = (73 + periodsNumber + ((nOPT + 1)*(RVol + 1)))/20.0;
		break;
	case 1:
		instFolder = "Multi-reservoir_instances/";
		system("mkdir Multi-reservoir_instances");
		linesStep = int(87 + (2 * periodsNumber) + ((nOPT + 1)*(RVol + 1)))
			/ 20.0;
		break;
	case 2:
		instFolder = "Single-reservoir_periods_instances";
		system("mkdir Single-reservoir_periods_instances");
		linesStep = 10000;
		break;
	default:
		instFolder = "Instances/";
		break;
	}

	//Creating the name of the instance
	if ((year - 2000) < 10){
		sStream << instFolder << "/" << "Suviana_0" << year - 2000;
	}
	else{
		sStream << instFolder << "/" << "Suviana_" << year - 2000;
	}
	if (month < 10){
		sStream << "0" << month;
	}
	else{
		sStream << month;
	}
	if (day < 10){
		sStream << "0" << day;
	}
	else{
		sStream << day;
	}
	sStream << "_" << periodsNumber << "_" << nOPT << "_" << RVol << "_";
	sStream << fixed << three_digits_string(v_min_modif) << "_";
	sStream << fixed << three_digits_string(v_max_modif) << "_";
	sStream << fixed << three_digits_string(v_0_modif) << "_";
	sStream << fixed << three_digits_string(v_T_modif) << ".dat";
	string fileName = sStream.str();
	sStream.str("");
	cout << fileName << endl;
	char instName[100];
	strcpy(instName, fileName.c_str());

	//Calculating the values of the instance
	//Q_i water flow
	double *qValues = new double[nOPT];
	qValues[0] = 0.0;
	for (int i = 1; i < nOPT; i++){
		qValues[i] = 8.4 + (42 - 8.4)*(i - 1) / (nOPT - 2);
	}

	//The jump
	double *jump = new double[RVol];
	for (int i = 0; i < RVol; i++){
		jump[i] = min_jump + ((max_jump - min_jump)*(i + 1)) / RVol;
	}

	//Eta values of the production function
	double *eta = new double[nOPT-1];
	for (int i = 0; i < nOPT-1; i++){
		eta[i] = 0;
		for (int j = 0; j < 7; j++){
			eta[i] += coeff_eta[j]*pow(qValues[i + 1], j);
		}
	}

	//P_ir produced power
	double **pValues = new double*[nOPT];
	pValues[0] = new double[RVol];
	for (int j = 0; j < RVol; j++){
		pValues[0][j] = 0.0;
	}
	for (int i = 1; i < nOPT; i++){
		pValues[i] = new double[RVol];
		for (int j = 0; j < RVol; j++){
			pValues[i][j] = 9.81 / 1000 * qValues[i] * eta[i - 1] *
				(jump[j] - (0.01 * qValues[i] * qValues[i]));
		}
	}

	//V volumes
	double *vValues = new double[RVol + 1];
	vValues[0] = v_min;
	for (int j = 0; j < RVol; j++){
		vValues[j + 1] = ((v_max - v_min)*j / (RVol - 1)) + v_min;
	}

	//Writing the instance
	if (verbose == 1)
		cout << "*** Writing instance            ***" << endl;

	ofstream  instanceGen;

	origPrecision = instanceGen.precision();

	if (verbose == 1)
		cout << "*** [";

	instanceGen.open(instName, ios::trunc);
	instanceGen << "# HYDROELECTRIC POWER STATION SINGLE RESERVOIR " <<
		"SINGLE TURBINE (1 week, data Milano, " << monthNames[month - 1] <<
		")\n\n";

	if (verbose == 1)
		print_perc(&linesCount, linesStep, 2);
	
	if (instFormat == 1){
		instanceGen << "# J is the number of reservoirs\n" <<
			"param J := 1;\n\n";

		if (verbose == 1)
			print_perc(&linesCount, linesStep, 3);
	}

	instanceGen << "# T is the number of time steps considered\n";
	instanceGen << "param T := " << periodsNumber <<
		";	# 24 time steps of one hour\n\n";
	
	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 3);

	if (instFormat != 1){
		instanceGen << "# inflows{PERIODS} is the external (given) " <<
			"water inflow for each time step [m^3/s]\n";

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, 1);
	}
	instanceGen << "# prices{PERIODS} is the unit price of the power " <<
		"generated/consumed at each time step [euros/MWh]\n";

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 1);

	if (instFormat == 2){
		instanceGen << "# v_min{PERIODS} is the lower bound on water " <<
			"volume in the reservoir for each time step [m^3]\n" <<
			"# v_max{PERIODS} is the upper bound on water " <<
			"volume in the reservoir for each time step [m^3]\n";

		if (verbose == 1)
			print_perc(&linesCount, linesStep, 2);
	}

	instanceGen <<
		"param:\tPERIODS:\t"; 
	if (instFormat != 1){
		instanceGen << "inflows\t " << " " << " " << " " << " ";
	}
	instanceGen << " prices";
	if (instFormat == 2){
		instanceGen << "	   v_min	   v_max";
	}
	instanceGen << " :=\n";

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 1);
	
	for (int i = 0; i < periodsNumber; i++){
		instanceGen << "\t\t" << i + 1 << "\t";
		for (int j = 0; j < 11; j++){
			instanceGen << " ";
		}
		if (instFormat != 1){
			instanceGen << fixed << setprecision(2) << (*inflows)[i] << "\t";
			for (int j = 0; j < 7; j++){
				instanceGen << " ";
			}
		}

		instanceGen << fixed << setprecision(2) << (*prices)[i];
		if (instFormat == 2){
			instanceGen << fixed <<
				setprecision(origPrecision) << "	" << v_min << "	"<< v_max;
		}

		instanceGen << "\n";
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, periodsNumber);

	instanceGen << fixed << setprecision(origPrecision) << ";\n\n";

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 2);

	instanceGen << "param delta_t    := 1;					# period " <<
		"duration [h]\n" <<
		"param rampup     := 70;					# RHS of the rampup " <<
		"constraint that limits the water-flow variation between two " <<
		"consecutive time steps [m^3/s]\n" <<
		"param rampdwn    := 70;					# RHS of the rampdown " <<
		"constraint that limits the water-flow variation between two " <<
		"consecutive time steps [m^3/s]\n";

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 3);

	if (instFormat == 0){
		instanceGen <<
			"param v_min      := " << v_min << ";			" <<
			"# lower bound on water " <<
			"volume in the reservoir [m^3]\n" <<
			"param v_max      := " << v_max << ";			" <<
			"# upper bound on water " <<
			"volume in the reservoir [m^3]\n";

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, 2);

	}
	if (instFormat == 1){
		 instanceGen <<
			 "\n# inflows{RESERVOIR,PERIODS} is the external (predicted) " <<
			 "water inflow for each time step for each reservoir " <<
			 "[m^3/s]\n" <<
			 "# v_min{RESERVOIR,PERIODS} is the lower bound on water " <<
			 "volume for each time step for each reservoir [m^3]\n" <<
			 "# v_max{RESERVOIR,PERIODS} is the upper bound on water " <<
			 "volume for each time step for each reservoir [m^3]\n" <<
			 "param:	RESERVOIRS:			 inflows	   v_min	   " <<
			 "v_max :=\n";
		 for (int i = 0; i < periodsNumber; i++){
			 if (i < 9){
				 instanceGen << fixed <<
					 "		1				  " << i + 1 << "	   ";
			 }
			 else{
				 instanceGen << fixed <<
					 "		1				 " << i + 1 << "	   ";
			 }

			 instanceGen << fixed << setprecision(2) <<
				 (*prices)[i] << "	" <<
				 setprecision(origPrecision) << v_min << "	"
				 << v_max << "\n";
		 }
		 instanceGen <<
			 ";\n\n";

		 //print percentage of written lines
		 if (verbose == 1)
			 print_perc(&linesCount, linesStep, (7 + periodsNumber));
	}

	instanceGen <<
		"param v_0        := " << v_0 <<
		";			# initial water volume in " <<
		"the reservoir [m^3]\n" <<
		"param v_T        := " << v_T <<
		";			# initial water volume in " <<
		"the reservoir [m^3]\n";
	instanceGen <<
		"param N_turbines := 1;					# number of turbines\n" <<
		"param N_pumps    := 1;					# number of pumps\n" <<
		"param pump_activation_via_turbine := 0;	# is the pump " <<
		"activated using the power produced by a turbine? 0 = no, 1 = yes " <<
		"(this influences how the cost of activating a pump is computed)\n" <<
		"param theta_min	 := 0;					# lower bound on the " <<
		"amount of water released in each time period [m^3/s]\n" <<
		"param s_max 	 := 0;					# maximum water spillage " <<
		"[m^3/s]\n\n";
	
	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 8);
	
	instanceGen <<
		"# qT_0{TURBINES} is the initial flow of each turbine [m^3/s]\n" <<
		"# g_0{TURBINES} is the initial status of each turbine. Is the " <<
		"turbine on? 0 = no, 1 = yes [m^3/s]\n" <<
		"# scT{TURBINES} is the setup cost for each turbine [euros]\n" <<
		"# nOPT{TURBINES} is the number of operational points (o.p.) " <<
		"for each turbine\n" <<
		"# q_min{TURBINES} is the minimum flow for each turbine [m^3/s]\n" <<
		"# q_max{TURBINES} is the maximum flow for each turbine [m^3/s]\n" <<
		"# wT_init{TURBINES} is the water needed to start up each turbine " <<
		"[m^3/s]\n" <<
		"# type{TURBINES} is the type of a turbine\n" <<
		"param:	TURBINES:	qT_0	g_0	         scT	nOPT	       " <<
		"q_min	       q_max	       wT_init	 type :=\n" <<
		"	    1	        0.00	  0	       75.00	  ";
	if (nOPT < 10){
		instanceGen << " ";
	}
	instanceGen << nOPT << "	        " <<
		"8.40	       42.00			  0.00	    L\n" <<
		";\n\n";

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 12);

	instanceGen << 
		"# qP_0{PUMPS} is the initial flow of each pump [m^3/s]\n" <<
		"# u_0{PUMPS} is the initial status of each pump. Is pump on? 0 = " <<
		"no, 1 = yes [m^3/s]\n" <<
		"# scP{PUMPS} is the setup cost of each pump [euros]\n" <<
		"# nOPP{PUMPS} is the number of o.p. for each pump\n" <<
		"# wP_init{PUMPS} is the water needed to start up each pump " <<
		"[m^3/s]\n" <<
		"# eP_init{PUMPS} is the energy needed to start up each pump " <<
		"[MWh]\n" <<
		"param:	PUMPS:	    qP_0	u_0	         scP	nOPP	       " <<
		"wP_init	       eP_init :=\n" <<
		"	    1	        0.00	  0	       75.00	   2			  " <<
		"0.00			  0.00\n" <<
		";\n\n";


	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 10);

	instanceGen << "# R is the number of intervals, each of which is " <<
		"associated with a volume: the first interval has volume v_min; " <<
		"the volumen associated\n" <<
		"# with each of the following R-1 intervals is computed as \"" <<
		"volume of previous interval\" + (v_max - v_min / R)\n" <<
		"param R			 := " << RVol << ";\n\n";

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 4);
	
	instanceGen << "# Q_i is the water flow corresponding to each o.p. " <<
		"of a turbine [m^3/s]\n" <<
		"param:					            Q_i :=\n";
	for (int i = 0; i < nOPT; i++){
		if (i < 9){
			instanceGen << fixed << "	    1\t          " << i + 1 <<
				"	          ";
		}
		else{
			instanceGen << fixed << "	    1\t         " << i + 1 <<
				"	          ";
		}
		instanceGen << fixed << setprecision(origPrecision);
		if (qValues[i] < 10){
			instanceGen << fixed << setprecision(2) << " " <<
				qValues[i] << "\n";
		}
		else{
			instanceGen << fixed << setprecision(2) << qValues[i] << "\n";
		}
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, (2 + nOPT));

	instanceGen << fixed << setprecision(origPrecision);
	instanceGen << ";\n\n" <<
		"# P_ir is the power produced by a turbine at each o.p. and " <<
		"each volume [MW]\n" <<
		"param:					            			   P_ir :=\n";
	for (int k = 0; k < RVol; k++){
		for (int i = 0; i < nOPT; i++){
			if (i < 9){
				instanceGen << "	    1\t          " << i + 1 <<
					"				  " << k + 1 << "	          ";
			}
			else{
				instanceGen << "	    1\t         " << i + 1 <<
					"				  " << k + 1 << "	          ";
			}
			if (pValues[i][k] < 10){
				instanceGen << " " << pValues[i][k] << "\n";
			}
			else{
				instanceGen << pValues[i][k] << "\n";
			}
		}
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, (4 + (nOPT*RVol)));

	instanceGen << ";\n\n" <<
		"# Q_u is the water flow corresponding to each o.p. of a pump" <<
		" [m^3/s]\n" <<
		"# P_u is the power produced by a pump at each o.p. [MW]\n" <<
		"param:					            Q_u	            P_u :=\n" <<
		"	    1	          1	           0.00	           0.00\n" <<
		"	    1	          2	         -26.98	         -21.40\n" <<
		";\n\n";
	
	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 9);

	instanceGen <<
		"# V is a vector providing lower and upper bounds on the water " <<
		"volume of each interval k, k = 1...R\n"
		"# For each interval k: V[k-1] is the lower bound and V[k] its " <<
		"upper bound\n"
		"param:	          V :=\n";
	for (int k = 0; k < RVol + 1; k++){
		instanceGen << fixed << k << "\t" << vValues[k] << "\n";
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, (4 + RVol));

	instanceGen << ";\n\n" <<
		"#t2p is the index of the pump associated with each turbine. t2p " <<
		"= -1 if the turbine has non corresponding pump\n" <<
		"param:         	t2p :=\n" << "	    1	      1\n" << ";\n";

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 6);

	if (instFormat == 1){
		instanceGen <<
			"\n#t2Up is the index of the uphill reservoir associated with " <<
			"each turbine\n#t2Dw is the index of the downhill reservoir " <<
			"associated with each turbine.\n" <<
			"#t2Up and t2Dw = -1 if there is not a corresponding reservoir" <<
			"= -1 if the turbine has non corresponding pump\n"
			"param:         	t2Up t2Dw :=\n" << "	    1	       " <<
			"1	-1\n" << ";\n";

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, 7);

	}

	instanceGen.close();
	if (verbose == 1)
		cout << "] 100% ***\n";

	delete[] qValues;
	delete[] jump;
	delete[] eta;
	for (int i = 0; i < nOPT; i++){
		delete[] pValues[i];
	}
	delete[] pValues;
	delete[] vValues;

	if (verbose == 1)
		cout << "*** Writing instance - Complete ***" << endl << endl;


	return 0;
}
