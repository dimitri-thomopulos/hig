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
 * @version  :1.06.1
 */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "write_instance.h"

using namespace std;

string monthNames[12] = { "January", "February", "March", "April", "May", 
"June", "July", "August", "September", "October", "November", "December" };

double const coeff_eta[7] = { 4.09863600116008, -1.25535942295343, 
0.160530264942775, -0.00976201903589132, 0.000309429429972963,
-4.92928898248035E-06, 0.0000000311519548768 };

double const coeff_k[7] = { 307.395, 0.0000388,
		-0.00000000000437, 2.65E-19, -8.87E-27,
		1.55E-34, -1.11E-42 };

int const hTurbine = 384;

double const min_jump[5] = { 268.20, 314.70, 144.00, 71.50, 38.25 };
double const max_jump[5] = { 319.70, 375.20, 171.70, 85.25, 45.60 };

double const jump_scale[5] = { 3.751, 4.401, 2.014, 1.000, 0.535 };

double const min_qValues[5] = { 0.5, 21, 1.4, 8.4, 0.1 };
double const max_qValues[5] = { 2.8, 104.6, 7, 42, 0.3 };

double const scale_prod[5] = { 1, 0.433, 2.6, 1, 10 };
double const scale_group[5] = { 2, 1, 1, 1, 2 };

int const t2Up[5] = { 0, 0, 1, 3, 2 };

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

//function to compleate a line  of empty colums in csv files
int complete_csv(ofstream& printer, int remaining_cols){
	for (int i = 0; i < remaining_cols; i++){
		printer << ";";
	}
	//printer << "check;"; command to verify csv indentation
	printer << "\n";
	return 0;
}

//function to set the volumes
int set_volumes(int instFormat, int res_number, int *v_min, int *v_max, 
	int *v_0, int *v_T, int *v_0_modif, int *v_T_modif, int *v_min_modif, 
	int *v_max_modif){
	if (instFormat == 2){
		for (int i = 0; i < res_number; i++){
			v_min[i] = v_LB[i] + (v_min_modif[i] * v_step);
			v_max[i] = v_UB[i] - (v_max_modif[i] * v_step);
			v_0[i] = v_LB[i] + (v_0_modif[i] * v_double_step);
			v_T[i] = v_LB[i] + (v_T_modif[i] * v_double_step);
		}
	}
	else{
		v_min[0] = v_LB[3] + (v_min_modif[0] * v_step);
		v_max[0] = v_UB[3] - (v_max_modif[0] * v_step);
		v_0[0] = v_LB[3] + (v_0_modif[0] * v_double_step);
		v_T[0] = v_LB[3] + (v_T_modif[0] * v_double_step);
	}
	
	return 0;
}

int write_instance(int instFormat, int year, int month, int day,
	int periodsNumber, int nOPT, double **prices, double **inflows, int RVol,
	int *v_0_modif, int *v_T_modif, int *v_min_modif, int *v_max_modif){
	stringstream sStream; //string to create the name of the file
	string instFolder; //path/name of the folder of instances
	int origPrecision; //variable to memorize the original output precision
	double linesCount = 0.0001; //counter of printed lines
	double linesStep = 0.0001; //number of lines to print a percentage after
	int verbose = 1; // 1 to print percentage of done lines, 0 otherwise
	int res_number = 1; // number of reservoirs
	int turb_number = 1; // number of turbines
	int temp_linestep = 0; //auxialiary line_step counter

	//setting the number of reservoirs
	if (instFormat == 2){
		res_number = MAX_RESERVOIR;
		turb_number = MAX_TURBINES;
	}

	int* v_min = (int*)malloc(res_number * sizeof(int));
	int* v_max = (int*)malloc(res_number * sizeof(int));
	int* v_0 = (int*)malloc(res_number * sizeof(int));
	int* v_T = (int*)malloc(res_number * sizeof(int));

	double* min_jump_t = (double*)malloc(res_number * sizeof(double));
	double* max_jump_t = (double*)malloc(res_number * sizeof(double));

	set_volumes(instFormat, res_number, v_min, v_max, v_0, v_T,
		v_0_modif, v_T_modif, v_min_modif, v_max_modif);

	//Creating instances folders
	switch (instFormat)
	{
	case 0:
		instFolder = "Single-reservoir_instances";
		system("mkdir Single-reservoir_instances");
		linesStep = (75 + periodsNumber + ((nOPT + 1)*(RVol + 1))) / 20.0;
		break;
	case 1:
		instFolder = "Multi-reservoir_instances/";
		system("mkdir Multi-reservoir_instances");
		linesStep = int(89 + (2 * periodsNumber) + ((nOPT + 1)*(RVol + 1)))
			/ 20.0;
		break;
	case 2:
		instFolder = "Multi-reservoir_instances";
		system("mkdir Multi-reservoir_instances");
		linesStep = int(99 + (2 * periodsNumber)
			+ ((nOPT + 1)*(RVol + 1)) + res_number + turb_number
			+ (RVol*(res_number - 1)) + ((nOPT)*(RVol + 1)*(turb_number - 1)))
			/ 20.0;
		break;
	case 3:
		instFolder = "Single-reservoir_periods_instances";
		system("mkdir Single-reservoir_periods_instances");
		linesStep = 10000;
		break;
	default:
		instFolder = "Instances/";
		break;
	}

	//Creating the name of the instance
	if (instFormat != 2){
		if ((year - 2000) < 10){
			sStream << instFolder << "/" << "Suviana_0" << year - 2000;
		}
		else{
			sStream << instFolder << "/" << "Suviana_" << year - 2000;
		}
	}
	else{
		if ((year - 2000) < 10){
			sStream << instFolder << "/" << "Reno_0" << year - 2000;
		}
		else{
			sStream << instFolder << "/" << "Reno_" << year - 2000;
		}
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
	sStream << "_" << periodsNumber << "_" << nOPT << "_" << RVol;
	if (instFormat != 2){
		sStream << "_";
		sStream << fixed << three_digits_string(v_min_modif[0]) << "_";
		sStream << fixed << three_digits_string(v_max_modif[0]) << "_";
		sStream << fixed << three_digits_string(v_0_modif[0]) << "_";
		sStream << fixed << three_digits_string(v_T_modif[0]);
	}
	else{
		for (int i = 0; i < res_number; i++){
			sStream << "_";
			sStream << fixed << v_min_modif[i];
			sStream << fixed << v_max_modif[i];
			sStream << fixed << v_0_modif[i];
			sStream << fixed << v_T_modif[i];
		}
	}
	sStream << ".dat";
	string fileName = sStream.str();
	sStream.str("");
	cout << fileName << endl;
	char instName[100];
	strcpy(instName, fileName.c_str());

	//Calculating the values of the instance
	//Q_i water flow

	double **qValues = new double*[turb_number];
	for (int t = 0; t < turb_number; t++){
		qValues[t] = new double[nOPT];
		qValues[t][0] = 0;
		for (int i = 1; i < nOPT; i++){
			if (instFormat != 2){
				qValues[t][i] = min_qValues[3] 
					+ (max_qValues[3] - min_qValues[3])
					*(i - 1) / (nOPT - 2);
			}
			else{
				qValues[t][i] = min_qValues[t] 
					+ (max_qValues[t] - min_qValues[t])
					*(i - 1) / (nOPT - 2);
			}
		}
	}

	//The jump
	for (int t = 0; t < turb_number; t++){
		if (instFormat != 2){
			min_jump_t[t] = -hTurbine;
			max_jump_t[t] = -hTurbine;
		}else{
			min_jump_t[t] = -hTurbine * jump_scale[t];
			max_jump_t[t] = -hTurbine * jump_scale[t];
		}
			
		for (int h = 0; h < 7; h++){
			if (instFormat != 2){
				min_jump_t[t] += (coeff_k[h] * pow((v_min[0]), h));
				max_jump_t[t] += (coeff_k[h] * pow((v_max[0]), h));
			}
			else{
				min_jump_t[t] += (coeff_k[h] * jump_scale[t] *
					pow((v_min[t2Up[t]] * v_LB[0] / v_LB[t2Up[t]]), h));
				max_jump_t[t] += (coeff_k[h] * jump_scale[t] *
					pow((v_max[t2Up[t]] * v_UB[0] / v_UB[t2Up[t]]), h));
			}
		}
	}

	double **jump = new double*[turb_number];
	for (int t = 0; t < turb_number; t++){
		jump[t] = new double[RVol];
		for (int i = 0; i < RVol; i++){
			/*if (instFormat != 2){
				jump[t][i] = min_jump[3] 
					+ ((max_jump[3] - min_jump[3])*(i + 1)) / RVol;
			}
			else{
				jump[t][i] = min_jump[t] 
					+ ((max_jump[t] - min_jump[t])*(i + 1)) / RVol;
			}*/
			jump[t][i] = min_jump_t[t]
				+ ((max_jump_t[t] - min_jump_t[t])*(i + 1)) / RVol;
		}
	}

	//Eta values of the production function
	double **eta = new double*[turb_number];
	for (int t = 0; t < turb_number; t++){
		eta[t] = new double[nOPT - 1];
		for (int i = 0; i < nOPT - 1; i++){
			eta[t][i] = 0;
			for (int j = 0; j < 7; j++){
				if (instFormat != 2){
					eta[t][i] += coeff_eta[j] 
						* pow((qValues[0][i + 1] * scale_prod[3]), j);
				}
				else{
					eta[t][i] += coeff_eta[j] 
						* pow((qValues[t][i + 1] * scale_prod[t]), j);
				}
			}
		}
	}

	//P_ir produced power
	double ***pValues = new double**[turb_number];
	for (int t = 0; t < turb_number; t++){
		pValues[t] = new double*[nOPT];
		pValues[t][0] = new double[RVol];
		for (int j = 0; j < RVol; j++){
			pValues[t][0][j] = 0.0;
		}
		for (int i = 1; i < nOPT; i++){
			pValues[t][i] = new double[RVol];
			for (int j = 0; j < RVol; j++){
				if (instFormat != 2){
					pValues[t][i][j] = 9.81 / scale_group[3] / 1000
						* qValues[t][i] * eta[t][i - 1] * (jump[t][j] 
						- (0.01 * qValues[t][i] * qValues[t][i]));
				}
				else{
					pValues[t][i][j] = 9.81 / scale_group[t] /1000
						* qValues[t][i] * eta[t][i - 1] * (jump[t][j]
						- (0.01 * qValues[t][i] * qValues[t][i]));
				}
			}
		}
	}

	//V volumes
	double **vValues = new double*[res_number];
	for (int t = 0; t < res_number; t++){
		vValues[t] = new double[RVol + 1];
		vValues[t][0] = v_min[t];
		if (RVol > 1){
			for (int j = 0; j < RVol; j++){
				vValues[t][j + 1] = ((v_max[t] - v_min[t])*j / (RVol - 1)) 
					+ v_min[t];
			}
		}
		else{
			vValues[t][1] = v_max[t];
		}
	}

	//Writing the instance
	if (verbose == 1)
		cout << "*** Writing instance            ***" << endl;

	ofstream  instanceGen;

	origPrecision = instanceGen.precision();

	if (verbose == 1)
		cout << "*** [";

	instanceGen.open(instName, ios::trunc);
	if (instFormat == 2){
		instanceGen << "# HYDROELECTRIC POWER STATION MULTI RESERVOIR " <<
			"MULTI TURBINE (1 week, data Milano, " << monthNames[month - 1] <<
			")\n\n";
	}
	else{
		instanceGen << "# HYDROELECTRIC POWER STATION SINGLE RESERVOIR " <<
			"SINGLE TURBINE (1 week, data Milano, " << monthNames[month - 1] <<
			")\n\n";
	}
	

	if (verbose == 1)
		print_perc(&linesCount, linesStep, 2);
	
	if ((instFormat == 1) || (instFormat == 2)){
		instanceGen << "# J is the number of reservoirs\n" <<
			"param J := " << res_number << ";\n\n";

		if (verbose == 1)
			print_perc(&linesCount, linesStep, 3);
	}

	instanceGen << "# T is the number of time steps considered\n";
	instanceGen << "param T := " << periodsNumber <<
		";	# 24 time steps of one hour\n\n";
	
	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 3);

	if ((instFormat != 1) && (instFormat != 2)){
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

	if (instFormat == 3){
		instanceGen << "# v_min{PERIODS} is the lower bound on water " <<
			"volume in the reservoir for each time step [m^3]\n" <<
			"# v_max{PERIODS} is the upper bound on water " <<
			"volume in the reservoir for each time step [m^3]\n";

		if (verbose == 1)
			print_perc(&linesCount, linesStep, 2);
	}

	instanceGen <<
		"param:\tPERIODS:\t"; 
	if ((instFormat != 1) && (instFormat != 2)){
		instanceGen << "inflows\t " << " " << " " << " " << " ";
	}
	instanceGen << " prices";
	if (instFormat == 3){
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
		if ((instFormat != 1) && (instFormat != 2)){
			instanceGen << fixed << setprecision(2) << (*inflows)[i] << "\t";
			for (int j = 0; j < 7; j++){
				instanceGen << " ";
			}
		}

		instanceGen << fixed << setprecision(2) << (*prices)[i];
		if (instFormat == 3){
			instanceGen << fixed <<
				setprecision(origPrecision) << "	" << v_min[0] << "	"
				<< v_max[0];
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
			"param v_min      := " << v_min[0] << ";			" <<
			"# lower bound on water " <<
			"volume in the reservoir [m^3]\n" <<
			"param v_max      := " << v_max[0] << ";			" <<
			"# upper bound on water " <<
			"volume in the reservoir [m^3]\n";

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, 2);

	}
	if ((instFormat == 1) || (instFormat == 2)){
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
		 for (int j = 0; j < res_number; j++){
			 for (int i = 0; i < periodsNumber; i++){
				 if (i < 9){
					 instanceGen << fixed <<
						 "		" << j + 1 << "				  " << 
						 i + 1 << "	   ";
				 }
				 else{
					 instanceGen << fixed <<
						 "		" << j +1 << "				 " << 
						 i + 1 << "	   ";
				 }

				 instanceGen << fixed << setprecision(2) <<
					 (*inflows)[i] << "		" <<
					 setprecision(origPrecision) << v_min[j] << "	"
					 << v_max[j] << "\n";
			 }
		 }
		 instanceGen <<
			 ";\n\n";

		 //print percentage of written lines
		 if (verbose == 1)
			 print_perc(&linesCount, linesStep, 
			 (7 + (periodsNumber*res_number)));
	}

	if (instFormat != 2){
		instanceGen <<
			"param v_0        := " << v_0[0] <<
			";			# initial water volume in " <<
			"the reservoir [m^3]\n" <<
			"param v_T        := " << v_T[0] <<
			";			# target water volume in " <<
			"the reservoir [m^3]\n";
	}
	else{
		instanceGen <<
			"# v_0{RESERVOIR} is intial water " <<
			"volume for each reservoir [m^3]\n" <<
			"# v_T{RESERVOIR} is the target water " <<
			"volume for each  reservoir [m^3]\n" <<
			"param:					 v_0	     " <<
			"v_T :=\n";
		for (int j = 0; j < res_number; j++){
			instanceGen << fixed <<
				"		" << j + 1 << "			";
			instanceGen << fixed << v_0[j] << "	"
				<< v_T[j] << "\n";
		}
		instanceGen << ";\n\n";
		temp_linestep = res_number + 1;
	}
	if (instFormat != 2){
		instanceGen <<
			"param N_turbines := 1;					# number of turbines\n" <<
			"param N_pumps    := 1;					# number of pumps\n";
	}
	else{
		instanceGen <<
			"param N_turbines := 5;					# number of turbines\n" <<
			"param N_pumps    := 2;					# number of pumps\n";
	}
	instanceGen <<
		"param pump_activation_via_turbine := 0;	# is the pump " <<
		"activated using the power produced by a turbine? 0 = no, 1 = yes " <<
		"(this influences how the cost of activating a pump is computed)\n" <<
		"param theta_min	 := 0;					# lower bound on the " <<
		"amount of water released in each time period [m^3/s]\n" <<
		"param s_max 	 := 0;					# maximum water spillage " <<
		"[m^3/s]\n\n";
	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, (8 + temp_linestep));
	
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
		"# plantT{TURBINES} index of the power plant the turbine " <<
		"belongs to\n" <<
		"param:	TURBINES:	qT_0	g_0	         scT	nOPT	       " <<
		"q_min	       q_max	       wT_init	 type	plantT:=\n";
	
	for (int t = 0; t < turb_number; t++){
		instanceGen <<
			"	    "<< t+1 << "	        0.00	  0	       75.00	  ";
		if (nOPT < 10){
			instanceGen << " ";
		}
		instanceGen << fixed << setprecision(2) << nOPT << "	       ";
		if (qValues[t][1] < 10){
			instanceGen << " ";
		}
		instanceGen << qValues[t][1] << "	      ";
		if (qValues[t][nOPT - 1] < 10){
			instanceGen << "	";
		}
		else{
			if (qValues[t][nOPT - 1] < 100){
				instanceGen << " ";
			}
		}
		instanceGen << qValues[t][nOPT - 1] <<
		"			  0.00	    L		 " << t + 1 << "\n";
	}
	instanceGen << fixed << setprecision(origPrecision) <<";\n\n";

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 11 + turb_number);

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
		"# plantP{PUMPS} index of the power plant the pump " <<
		"belongs to\n" <<
		"param:	PUMPS:	    qP_0	u_0	         scP	nOPP	       " <<
		"wP_init	       eP_init	plantP:=\n" <<
		"	    1	        0.00	  0	       75.00	   2			  " <<
		"0.00			  0.00		 1\n";
	if (instFormat == 2){
		instanceGen <<
			"	    2	        0.00	  0	       75.00	   2"<<
			"			  0.00			  0.00		 2\n";
	}
	instanceGen << ";\n\n";


	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 10);

	if (instFormat != 2){
		instanceGen << "# R";
	}
	else{
		instanceGen << "# R(RESERVOIRS)";
	}
	instanceGen << " is the number of intervals, each of which is " <<
		"associated with a volume: the first interval has volume v_min; " <<
		"the volume associated\n" <<
		"# with each of the following R-1 intervals is computed as \"" <<
		"volume of previous interval\" + (v_max - v_min / R)\n";
	if (instFormat != 2){
		instanceGen << "param R				:= " << RVol << ";\n\n";
	}
	else{
		instanceGen << "param:				R:=\n";
		for (int j = 0; j < res_number; j++){
			instanceGen << "			   "<< j + 1 << "	" << RVol << "\n";
		}
		instanceGen << ";\n\n";
	}
	

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 4);
	
	instanceGen << "# Q_i is the water flow corresponding to each o.p. " <<
		"of a turbine [m^3/s]\n" <<
		"param:					            Q_i :=\n";
	for (int t = 0; t < turb_number; t++){
		for (int i = 0; i < nOPT; i++){
			if (i < 9){
				instanceGen << fixed << "	    " << t + 1 << "\t          " <<
					i + 1 << "	         ";
			}
			else{
				instanceGen << fixed << "	    " << t + 1 << "\t         " <<
					i + 1 << "	         ";
			}
			instanceGen << fixed << setprecision(origPrecision);
			if (qValues[t][i] >= 100){
				instanceGen << fixed << setprecision(2) << 
					qValues[t][i] << "\n";
			}
			else{
				if (qValues[t][i] >= 10){
					instanceGen << fixed << setprecision(2) << " " <<
						qValues[t][i] << "\n";
				}
				else{
					instanceGen << fixed << setprecision(2) << "  " <<
						qValues[t][i] << "\n";
				}
			}
		}
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, (2 + (nOPT*turb_number)));

	instanceGen << fixed << setprecision(origPrecision);
	instanceGen << ";\n\n" <<
		"# P_ir is the power produced by a turbine at each o.p. and " <<
		"each volume [MW]\n" <<
		"param:												    P_ir :=\n";
	for (int t = 0; t < turb_number; t++){
		for (int k = 0; k < RVol; k++){
			for (int i = 0; i < nOPT; i++){
				if (i < 9){
					instanceGen << "	    " << t + 1 << "\t          " <<
						i + 1 << "				  " << k + 1 << 
						"	          ";
				}
				else{
					instanceGen << "	    " << t + 1 << "\t         " <<
						i + 1 << "				  " << k + 1 << 
						"	          ";
				}
				if (pValues[t][i][k] >= 100){
					instanceGen << pValues[t][i][k] << "\n";
				}
				else{
					if (pValues[t][i][k] >= 10){
						instanceGen << " " << pValues[t][i][k] << "\n";
					}
					else{
						instanceGen << "  " << pValues[t][i][k] << "\n";
					}
				}
			}
		}
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, (4 + (nOPT*RVol*turb_number)));

	instanceGen << ";\n\n" <<
		"# Q_u is the water flow corresponding to each o.p. of a pump" <<
		" [m^3/s]\n" <<
		"# P_u is the power consumed by a pump at each o.p. [MW]\n" <<
		"param:					            Q_u	            P_u :=\n";
	if (instFormat != 2){
		instanceGen <<
			"	    1	          1	           0.00	           0.00\n" <<
			"	    1	          2	         -26.98	         -21.40\n" <<
			";\n\n";

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, 9);
	}
	else{
		instanceGen <<
			"	    1	          1	           0.00	           0.00\n" <<
			"	    1	          2	         -67.19	        -262.18\n" <<
			"	    2	          1	           0.00	           0.00\n" <<
			"	    2	          2	         -26.98	         -21.40\n" <<
			";\n\n";

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, 11);
	}

	if (instFormat != 2){
		instanceGen <<
			"# V is a vector providing lower and upper bounds on the water " <<
			"volume of each interval k, k = 1...R\n"
			"# For each interval k: V[k-1] is the lower bound and V[k] its " <<
			"upper bound\n"
			"param:	           V :=\n";
		for (int k = 0; k < RVol + 1; k++){
			instanceGen << fixed << setprecision(origPrecision) << "	   " << 
				k << "\t";
			instanceGen << fixed << setprecision(0) << vValues[0][k] << "\n";
		}

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, (4 + RVol));
	}
	else{
		instanceGen <<
			"# V{RESERVOIR,R} is lower and upper bounds on the water " <<
			"volume for each reservoir j for each interval k, " << 
			"k = 1...R\n" <<
			"# For each reservoir j and interval k: V[j,k-1] is the lower " <<
			"bound and V[j,k] its upper bound\n"
			"param:							   " <<
			"V :=\n";
		for (int j = 0; j < res_number; j++){
			for (int k = 0; k < RVol + 1; k++){
				instanceGen << fixed << setprecision(origPrecision) <<
					"		" << j + 1 << "				 ";
				instanceGen << fixed << setprecision(0) << k <<
					"	" << vValues[j][k] << "\n";
			}
		}

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, (4 + (RVol*res_number)));
	}

	if (instFormat != 2){
		instanceGen << ";\n\n" <<
			"#t2p is the index of the pump associated with each turbine. " <<
			"t2p = -1 if the turbine has non corresponding pump\n" <<
			"param:         	t2p :=\n" << "	    1	      1\n" <<
			";\n";
	}
	else{
		instanceGen << ";\n\n" <<
			"#t2p is the index of the pump associated with each turbine. " <<
			"t2p = -1 if the turbine has non corresponding pump\n" <<
			"param:         	t2p :=\n" << "	    1	     -1\n" <<
			"	    2	      1\n" <<
			"	    3	     -1\n" <<
			"	    4	      2\n" <<
			"	    5	     -1\n" <<
			";\n";
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 5 + res_number);

	if (instFormat == 1){
		instanceGen <<
			"\n#t2Up is the index of the upstream reservoir associated with" <<
			" each turbine\n#t2Dw is the index of the downstream reservoir " <<
			"associated with each turbine.\n" <<
			"#t2Up and t2Dw = -1 if there is not a corresponding reservoir" <<
			"\n#tDelay is the delay [s] in flow from the upstream reservoir" <<
			" to the corresponding downstream reservoir\n" <<
			"#tDelay = 0 if 0 or there is not a corresponding reservoir\n" <<
			"param:         	t2Up  t2Dw tDelay:=\n" << "	    1	       " <<
			"1	-1	    0\n" << 
			";\n";

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, 8 + res_number);
	}

	if (instFormat == 2){
		instanceGen <<
			"\n#t2Up is the index of the upstream reservoir associated with" <<
			" each turbine\n#t2Dw is the index of the downstream reservoir " <<
			"associated with each turbine.\n" <<
			"#t2Up and t2Dw = -1 if there is not a corresponding reservoir" <<
			"\n#tDelay is the delay [s] in flow from the upstream reservoir" <<
			" to the corresponding downstream reservoir\n" <<
			"#tDelay = 0 if 0 or there is not a corresponding reservoir\n" <<
			"param:         	t2Up  t2Dw tDelay:=\n" << 
			"	    1	       1	 2	    0\n" <<
			"	    2	       1	 4	    0\n" <<
			"	    3	       2	-1	    0\n" <<
			"	    4	       4	-1	    0\n" <<
			"	    5	       3	 4	    0\n" <<
			";\n";

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, 8 + res_number);
	}

	instanceGen.close();
	if (verbose == 1)
		cout << "] 100% ***\n";

	for (int i = 0; i < turb_number; i++){
		delete[] qValues[i];
	}
	delete[] qValues;
	delete[] jump;
	for (int i = 0; i < turb_number; i++){
		delete[] eta[i];
	}
	delete[] eta;
	for (int i = 0; i < turb_number; i++){
		for (int j = 0; j < nOPT; j++){
			delete[] pValues[i][j];
		}
		delete[] pValues[i];
	}
	delete[] pValues;
	for (int i = 0; i < res_number; i++){
		delete[] vValues[i];
	}
	delete[] vValues;

	if (verbose == 1)
		cout << "*** Writing instance - Complete ***" << endl << endl;


	return 0;
}

int write_csv_instance(int instFormat, int year, int month, int day,
	int periodsNumber, int nOPT, double **prices, double **inflows, int RVol,
	int *v_0_modif, int *v_T_modif, int *v_min_modif, int *v_max_modif){
	stringstream sStream; //string to create the name of the file
	string instFolder; //path/name of the folder of instances
	int origPrecision; //variable to memorize the original output precision
	double linesCount = 0.0001; //counter of printed lines
	double linesStep = 0.0001; //number of lines to print a percentage after
	int verbose = 1; // 1 to print percentage of done lines, 0 otherwise
	int max_cols = 11;  // maximum number of csv columns
	int temp_col = 0; //auxiliary counter of already assigned csv columns 

	int res_number = 1; // number of reservoirs
	int turb_number = 1; // number of turbines
	int temp_linestep = 0; //auxialiary line_step counter

	//setting the number of reservoirs
	if (instFormat == 2){
		res_number = 4;
		turb_number = 5;
	}

	int* v_min = (int*)malloc(res_number * sizeof(int));
	int* v_max = (int*)malloc(res_number * sizeof(int));
	int* v_0 = (int*)malloc(res_number * sizeof(int));
	int* v_T = (int*)malloc(res_number * sizeof(int));

	double* min_jump_t = (double*)malloc(res_number * sizeof(double));
	double* max_jump_t = (double*)malloc(res_number * sizeof(double));

	set_volumes(instFormat, res_number, v_min, v_max, v_0, v_T,
		v_0_modif, v_T_modif, v_min_modif, v_max_modif);

	//Creating instances folders
	switch (instFormat)
	{
	case 0:
		instFolder = "Single-reservoir_instances";
		system("mkdir Single-reservoir_instances");
		linesStep = (75 + periodsNumber + ((nOPT + 1)*(RVol + 1))) / 20.0;
		break;
	case 1:
		instFolder = "Multi-reservoir_instances/";
		system("mkdir Multi-reservoir_instances");
		linesStep = int(89 + (2 * periodsNumber) + ((nOPT + 1)*(RVol + 1)))
			/ 20.0;
		break;
	case 2:
		instFolder = "Multi-reservoir_instances";
		system("mkdir Multi-reservoir_instances");
		linesStep = int(99 + (2 * periodsNumber)
			+ ((nOPT + 1)*(RVol + 1)) + res_number + turb_number
			+ (RVol*(res_number - 1)) + ((nOPT)*(RVol + 1)*(turb_number - 1)))
			/ 20.0;
		break;
	case 3:
		instFolder = "Single-reservoir_periods_instances";
		system("mkdir Single-reservoir_periods_instances");
		linesStep = 10000;
		break;
	default:
		instFolder = "Instances/";
		break;
	}

	//Creating the name of the instance
	if (instFormat != 2){
		if ((year - 2000) < 10){
			sStream << instFolder << "/" << "Suviana_0" << year - 2000;
		}
		else{
			sStream << instFolder << "/" << "Suviana_" << year - 2000;
		}
	}
	else{
		if ((year - 2000) < 10){
			sStream << instFolder << "/" << "Reno_0" << year - 2000;
		}
		else{
			sStream << instFolder << "/" << "Reno_" << year - 2000;
		}
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
	sStream << "_" << periodsNumber << "_" << nOPT << "_" << RVol;
	if (instFormat != 2){
		sStream << "_";
		sStream << fixed << three_digits_string(v_min_modif[0]) << "_";
		sStream << fixed << three_digits_string(v_max_modif[0]) << "_";
		sStream << fixed << three_digits_string(v_0_modif[0]) << "_";
		sStream << fixed << three_digits_string(v_T_modif[0]);
	}
	else{
		for (int i = 0; i < res_number; i++){
			sStream << "_";
			sStream << fixed << v_min_modif[i];
			sStream << fixed << v_max_modif[i];
			sStream << fixed << v_0_modif[i];
			sStream << fixed << v_T_modif[i];
		}
	}
	sStream << ".csv";
	string fileName = sStream.str();
	sStream.str("");
	cout << fileName << endl;
	char instName[100];
	strcpy(instName, fileName.c_str());

	//Calculating the values of the instance
	//Q_i water flow

	double **qValues = new double*[turb_number];
	for (int t = 0; t < turb_number; t++){
		qValues[t] = new double[nOPT];
		qValues[t][0] = 0;
		for (int i = 1; i < nOPT; i++){
			if (instFormat != 2){
				qValues[t][i] = min_qValues[3] 
					+ (max_qValues[3] - min_qValues[3])
					*(i - 1) / (nOPT - 2);
			}
			else{
				qValues[t][i] = min_qValues[t] 
					+ (max_qValues[t] - min_qValues[t])
					*(i - 1) / (nOPT - 2);
			}
		}
	}

	//The jump
	for (int t = 0; t < turb_number; t++){
		if (instFormat != 2){
			min_jump_t[t] = -hTurbine;
			max_jump_t[t] = -hTurbine;
		}else{
			min_jump_t[t] = -hTurbine * jump_scale[t];
			max_jump_t[t] = -hTurbine * jump_scale[t];
		}
			
		for (int h = 0; h < 7; h++){
			if (instFormat != 2){
				min_jump_t[t] += (coeff_k[h] * pow((v_min[0]), h));
				max_jump_t[t] += (coeff_k[h] * pow((v_max[0]), h));
			}
			else{
				min_jump_t[t] += (coeff_k[h] * jump_scale[t] *
					pow((v_min[t2Up[t]] * v_LB[0] / v_LB[t2Up[t]]), h));
				max_jump_t[t] += (coeff_k[h] * jump_scale[t] *
					pow((v_max[t2Up[t]] * v_UB[0] / v_UB[t2Up[t]]), h));
			}
		}
	}

	double **jump = new double*[turb_number];
	for (int t = 0; t < turb_number; t++){
		jump[t] = new double[RVol];
		for (int i = 0; i < RVol; i++){
			/*if (instFormat != 2){
				jump[t][i] = min_jump[3] 
					+ ((max_jump[3] - min_jump[3])*(i + 1)) / RVol;
			}
			else{
				jump[t][i] = min_jump[t] 
					+ ((max_jump[t] - min_jump[t])*(i + 1)) / RVol;
			}*/
			jump[t][i] = min_jump_t[t]
				+ ((max_jump_t[t] - min_jump_t[t])*(i + 1)) / RVol;
		}
	}

	//Eta values of the production function
	double **eta = new double*[turb_number];
	for (int t = 0; t < turb_number; t++){
		eta[t] = new double[nOPT - 1];
		for (int i = 0; i < nOPT - 1; i++){
			eta[t][i] = 0;
			for (int j = 0; j < 7; j++){
				if (instFormat != 2){
					eta[t][i] += coeff_eta[j] 
						* pow((qValues[0][i + 1] * scale_prod[3]), j);
				}
				else{
					eta[t][i] += coeff_eta[j] 
						* pow((qValues[t][i + 1] * scale_prod[t]), j);
				}
			}
		}
	}

	//P_ir produced power
	double ***pValues = new double**[turb_number];
	for (int t = 0; t < turb_number; t++){
		pValues[t] = new double*[nOPT];
		pValues[t][0] = new double[RVol];
		for (int j = 0; j < RVol; j++){
			pValues[t][0][j] = 0.0;
		}
		for (int i = 1; i < nOPT; i++){
			pValues[t][i] = new double[RVol];
			for (int j = 0; j < RVol; j++){
				if (instFormat != 2){
					pValues[t][i][j] = 9.81 / scale_group[3] / 1000
						* qValues[t][i] * eta[t][i - 1] * (jump[t][j]
						- (0.01 * qValues[t][i] * qValues[t][i]));
				}
				else{
					pValues[t][i][j] = 9.81 / scale_group[t] / 1000
						* qValues[t][i] * eta[t][i - 1] * (jump[t][j]
						- (0.01 * qValues[t][i] * qValues[t][i]));
				}
			}
		}
	}

	//V volumes
	double **vValues = new double*[res_number];
	for (int t = 0; t < res_number; t++){
		vValues[t] = new double[RVol + 1];
		vValues[t][0] = v_min[t];
		if (RVol > 1){
			for (int j = 0; j < RVol; j++){
				vValues[t][j + 1] = ((v_max[t] - v_min[t])*j / (RVol - 1))
					+ v_min[t];
			}
		}
		else{
			vValues[t][1] = v_max[t];
		}
	}

	//Writing the instance
	if (verbose == 1)
		cout << "*** Writing instance            ***" << endl;

	ofstream  instanceGen;

	origPrecision = instanceGen.precision();

	if (verbose == 1)
		cout << "*** [";

	instanceGen.open(instName, ios::trunc);

	if ((instFormat == 1) || (instFormat == 2)){
		instanceGen << "J;" << res_number << ";";
		complete_csv(instanceGen, max_cols - 2);

		if (verbose == 1)
			print_perc(&linesCount, linesStep, 1);
	}

	instanceGen << "T;" << periodsNumber <<
		";";
	complete_csv(instanceGen, max_cols - 2);
	
	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 1);

	instanceGen <<
		"PERIODS ";
	if ((instFormat != 1) && (instFormat != 2)){
		instanceGen << "inflows ";
	}
	instanceGen << "prices";
	if (instFormat == 3){
		instanceGen << " v_min v_max";
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 1);

	for (int i = 0; i < periodsNumber; i++){
		instanceGen << ";" << i + 1 << ";";
		if ((instFormat != 1) && (instFormat != 2)){
			instanceGen << fixed << setprecision(2) << (*inflows)[i] << ";";
			temp_col = 1;
		}
		instanceGen << fixed << setprecision(2) << (*prices)[i];
		if (instFormat == 3){
			instanceGen << fixed <<
				setprecision(origPrecision) << ";" << v_min[0] << ";" <<
				v_max[0];
			temp_col = temp_col + 2;
		}

		instanceGen << ";";
		complete_csv(instanceGen, max_cols - 3 - temp_col);
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, periodsNumber);

	instanceGen << fixed << setprecision(origPrecision);

	instanceGen << "delta_t;1;";
	complete_csv(instanceGen, max_cols - 2);
	instanceGen << "rampup;70;";
	complete_csv(instanceGen, max_cols - 2);
	instanceGen << "rampdwn;70;";
	complete_csv(instanceGen, max_cols - 2);

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 3);

	if (instFormat == 0){
		instanceGen << "v_min;" << v_min[0] << ";";
		complete_csv(instanceGen, max_cols - 2);
		instanceGen << "v_max;" << v_max[0] << ";";
		complete_csv(instanceGen, max_cols - 2);

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, 2);

	}
	if ((instFormat == 1) || (instFormat == 2)){
		instanceGen <<
			"RESERVOIRS inflows v_min v_max";
		for (int j = 0; j < res_number; j++){
			for (int i = 0; i < periodsNumber; i++){
				if (i < 9){
					instanceGen << fixed <<
						";" << j + 1 << ";" << i + 1 << ";";
				}
				else{
					instanceGen << fixed <<
						";" << j + 1 << ";" << i + 1 << ";";
				}

				instanceGen << fixed << setprecision(2) <<
					(*inflows)[i] << ";" <<
					setprecision(origPrecision) << v_min[j] << ";"
					<< v_max[j] << ";";
				complete_csv(instanceGen, max_cols - 5);
			}
		}

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, ((periodsNumber*res_number)));
	}

	if (instFormat != 2){
		instanceGen << "v_0;" << v_0[0] << ";";
		complete_csv(instanceGen, max_cols - 2);
		instanceGen << "v_T;" << v_T[0] << ";";
		complete_csv(instanceGen, max_cols - 2);
	}
	else{
		instanceGen << "RESERVOIR v_0 v_T;";
		instanceGen << 1 << ";" << v_0[0] << ";" << v_T[0] << ";";
		complete_csv(instanceGen, max_cols - 4);
		for (int j = 1; j < res_number; j++){
			instanceGen << ";" << j + 1 << ";" << v_0[j] << ";" << v_T[j] <<
				";";
			complete_csv(instanceGen, max_cols - 4);
		}
	}

	if (instFormat != 2){
		instanceGen << "N_turbines;1;";
		complete_csv(instanceGen, max_cols - 2);
		instanceGen << "N_pumps;1;";
		complete_csv(instanceGen, max_cols - 2);
	}
	else{
		instanceGen << "N_turbines;5;";
		complete_csv(instanceGen, max_cols - 2);
		instanceGen << "N_pumps;2;";
		complete_csv(instanceGen, max_cols - 2);
	}
	instanceGen << "pump_activation_via_turbine;0;";
	complete_csv(instanceGen, max_cols - 2);
	instanceGen << "theta_min;0;";
	complete_csv(instanceGen, max_cols - 2);
	instanceGen << "s_max;0;";
	complete_csv(instanceGen, max_cols - 2);

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 6 + res_number);

	instanceGen <<
		"TURBINES qT_0 g_0 scT nOPT q_min q_max wT_init type plantT";
	instanceGen <<
		";1;0.00;0;75.00;";
	instanceGen << nOPT << ";" <<
		qValues[0][1] << "; " << qValues[0][nOPT - 1] << ";0.00;L;1;";
	complete_csv(instanceGen, max_cols - 10);
	for (int t = 1; t < turb_number; t++){
		instanceGen <<
			";" << t + 1 << ";0.00;0;75.00;";
		instanceGen << nOPT << ";" <<
			qValues[t][1] << ";" << qValues[t][nOPT - 1] << ";0.00;L;" << 
			t + 1 << ";";
		complete_csv(instanceGen, max_cols - 10);
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, turb_number);

	instanceGen <<
		"PUMPS qP_0 u_0 scP nOPP wP_init eP_init plantP;" <<
		"1;0.00;0;75.00;2;0.00;0.00;1;";
	complete_csv(instanceGen, max_cols - 8);
	if (instFormat == 2){
		instanceGen <<
			"PUMPS qP_0 u_0 scP nOPP wP_init eP_init plantP;" <<
			"2;0.00;0;75.00;2;0.00;0.00;2;";
		complete_csv(instanceGen, max_cols - 8);
	}


	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 1);
	if (instFormat != 2){
		instanceGen << "R;" << RVol << ";";
		complete_csv(instanceGen, max_cols - 2);
	}
	else{
		instanceGen << "RESERVOIR R;1;" << RVol << ";";
		complete_csv(instanceGen, max_cols - 3);
		for (int j = 1; j < res_number; j++){
			instanceGen << ";" << j + 1 << ";" << RVol << ";";
			complete_csv(instanceGen, max_cols - 3);
		}
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, 1);

	instanceGen << "TURBINES NOPT Q_i";
	for (int t = 0; t < turb_number; t++){
		for (int i = 0; i < nOPT; i++){
			if (i < 9){
				instanceGen << fixed << ";" << t + 1 << ";" << i + 1 << ";";
			}
			else{
				instanceGen << fixed << ";" << t + 1 << ";" << i + 1 << ";";
			}
			instanceGen << fixed << setprecision(origPrecision);
			instanceGen << fixed << setprecision(2) << qValues[t][i] << ";";
			complete_csv(instanceGen, max_cols - 4);
		}
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, (nOPT*turb_number));

	instanceGen << fixed << setprecision(origPrecision);
	instanceGen << "TURBINES NOPT VOLUMES P_ir";
	for (int t = 0; t < turb_number; t++){
		for (int k = 0; k < RVol; k++){
			for (int i = 0; i < nOPT; i++){
				if (i < 9){
					instanceGen << ";" << t + 1 << ";" << i + 1 <<
						";" << k + 1 << ";";
				}
				else{
					instanceGen << ";" << t + 1 << ";" << i + 1 <<
						";" << k + 1 << ";";
				}
				instanceGen << pValues[t][i][k] << ";";
				complete_csv(instanceGen, max_cols - 5);
			}
		}
	}

	//print percentage of written lines
	if (verbose == 1)
		print_perc(&linesCount, linesStep, ((nOPT*RVol*turb_number)));

	if (instFormat != 2){
		instanceGen << "PUMPS NOPP Q_u P_u" <<
			";1;1;0.00;0.00;";
		complete_csv(instanceGen, max_cols - 5);
		instanceGen << ";1;2;-26.98;-21.40;";
		complete_csv(instanceGen, max_cols - 5);

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, 2);
	}
	else{
		instanceGen << "PUMPS NOPP Q_u P_u" <<
			";1;1;0.00;0.00;";
		complete_csv(instanceGen, max_cols - 5);
		instanceGen << ";1;2;-67.19;-262.18;";
		complete_csv(instanceGen, max_cols - 5);
		instanceGen << ";2;1;0.00;0.00;";
		complete_csv(instanceGen, max_cols - 5);
		instanceGen << ";2;2;-26.98;-21.40;";
		complete_csv(instanceGen, max_cols - 5);

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, 4);
	}

	if (instFormat != 2){
		instanceGen <<
			"k V";
		for (int k = 0; k < RVol + 1; k++){
			instanceGen << fixed << ";" << k << ";" << vValues[0][k] << ";";
			complete_csv(instanceGen, max_cols - 3);
		}

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, (RVol));
	}
	else{
		instanceGen <<
			"RERSERVOIR k V";
		for (int j = 0; j < res_number; j++){
			for (int k = 0; k < RVol + 1; k++){
				instanceGen << fixed << setprecision(0) << ";" << j + 1 << 
					";" << k << ";" <<
					vValues[j][k] << ";";
				complete_csv(instanceGen, max_cols - 3);
			}
		}

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, (RVol*res_number));
	}

	if (instFormat != 2){
		instanceGen << fixed << setprecision(origPrecision) << 
			"TURBINES t2p" << ";1;1;";
		complete_csv(instanceGen, max_cols - 3);
	}
	else{
		instanceGen << "TURBINES t2p" << ";1;-1;";
		complete_csv(instanceGen, max_cols - 3);
		instanceGen << ";2;1;";
		complete_csv(instanceGen, max_cols - 3);
		instanceGen << ";3;-1;";
		complete_csv(instanceGen, max_cols - 3);
		instanceGen << ";4;2;";
		complete_csv(instanceGen, max_cols - 3);
		instanceGen << ";5;-1;";
		complete_csv(instanceGen, max_cols - 3);
	}

	//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, res_number);

	if (instFormat == 1){
		instanceGen <<
			"RESERVOIRS t2Up t2Dw tDelay" << ";1;1;-1;0;";
		complete_csv(instanceGen, max_cols - 5);

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, 1);

	}

	if (instFormat == 2){
		instanceGen <<
			"RESERVOIRS t2Up t2Dw tDelay" << ";1;1;2;0;";
		complete_csv(instanceGen, max_cols - 5);
		instanceGen << ";2;1;4;0;";
		complete_csv(instanceGen, max_cols - 5);
		instanceGen << ";3;2;-1;0;";
		complete_csv(instanceGen, max_cols - 5);
		instanceGen << ";4;4;-1;0;";
		complete_csv(instanceGen, max_cols - 5);
		instanceGen << ";5;3;4;0;";
		complete_csv(instanceGen, max_cols - 5);

		//print percentage of written lines
		if (verbose == 1)
			print_perc(&linesCount, linesStep, res_number);

	}

	instanceGen.close();
	if (verbose == 1)
		cout << "] 100% ***\n";

	for (int i = 0; i < turb_number; i++){
		delete[] qValues[i];
	}
	delete[] qValues;
	delete[] jump;
	for (int i = 0; i < turb_number; i++){
		delete[] eta[i];
	}
	delete[] eta;
	for (int i = 0; i < turb_number; i++){
		for (int j = 0; j < nOPT; j++){
			delete[] pValues[i][j];
		}
		delete[] pValues[i];
	}
	delete[] pValues;
	for (int i = 0; i < res_number; i++){
		delete[] vValues[i];
	}
	delete[] vValues;

	if (verbose == 1)
		cout << "*** Writing instance - Complete ***" << endl << endl;


	return 0;
}
