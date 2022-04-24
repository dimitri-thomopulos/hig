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

/* @file     :Main.cpp
 * @brief    :Main functions
 * @author   :Dimitri Thomopulos
 * @date     :20180730
 * @version  :1.02
 */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "head.h"

using namespace std;

int const year_LB = 2004;
int const year_UB = 2012;
int const month_LB = 1;
int const month_UB = 12;
int const day_LB = 1;
int const day_UB[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int const periodsNumber_LB = 24;
int const periodsNumber_UB = 168;
int const nOPT_LB = 3;
int const nOPT_UB = 36;
int const RVol_LB = 1;
int const RVol_UB = 25;

int v_0_modif_LB = 0;
int v_0_modif_UB = 900;
int v_T_modif_LB = 0;
int v_T_modif_UB = 900;

int const v_min_LB = 15000000;
int const v_min_UB = 24000000;
int const v_max_LB = 24000000;
int const v_max_UB = 33000000;

int const v_min_modif_LB = 0;
int const v_min_modif_UB = 900;
int const v_max_modif_LB = 0;
int const v_max_modif_UB = 900;

int rand_value(int LBValue, int UBValue){
	int randNum = rand() % (UBValue - LBValue + 1) + LBValue;
	return randNum;
}

int is_leap_year(int year, int month){
	if (month == 2){
		if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
			return 1;
	}
	return 0;
}

bool is_digits(const std::string &str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

int read_discrete_value(int LBValue, int UBValue, int defaultValue, 
	int stepValue)
{
	int varValue;
	string inputReader;
	int tempValue; //auxiliary value to count step values

	cout << "\nAn integer value in {";
	
	tempValue = LBValue;
	while (tempValue < UBValue){
		cout << tempValue << ", ";
		tempValue += stepValue;
	}
	cout << UBValue<< "}" <<
		" is required. Press enter for the default value { " <<
		defaultValue << " }: ";

	cin.clear();
	getline(cin, inputReader);
	if (inputReader == "") {
		varValue = defaultValue;
		cout << "Default value: " << varValue << "\n";
	}
	else{
		if (!(is_digits(inputReader))) {
			varValue = defaultValue;
			cout << "Wrong value, therefore the default value is assumed: " <<
				varValue << "\n";
		}
		else{
			varValue = atoi(inputReader.c_str());
			if (varValue < LBValue || varValue > UBValue){
				varValue = defaultValue;
				cout << "The value exceeded the bounds, therefore the " <<
					"default value is assumed: " << varValue << "\n";
			}
			else{
				if (varValue%stepValue != 0){
					varValue = defaultValue;
					cout << "The value in not one of the available values, " <<
						"therefore the default value is assumed: " << 
						varValue << "\n";
				}
			}
		}
	}
	cout << endl;
	return (varValue);
}

int read_value(int LBValue, int UBValue, int defaultValue)
{
	int varValue;
	string inputReader;

	cout << "\nAn integer value in [" << LBValue << "," << UBValue << "]" <<
		" is required. Press enter for the default value { " <<
		defaultValue << " }: ";

	cin.clear();
	getline(cin, inputReader);
	if (inputReader == "") {
		varValue = defaultValue;
		cout << "Default value: " << varValue << "\n";
	}
	else{
		if (!(is_digits(inputReader))) {
			varValue = defaultValue;
			cout << "Wrong value, therefore the default value is assumed: " <<
				varValue << "\n";
		}
		else{
			varValue = atoi(inputReader.c_str());
			if (varValue < LBValue || varValue > UBValue){
				varValue = defaultValue;
				cout << "The value exceeded the bounds, therefore the " <<
					"default value is assumed: " << varValue << "\n";
			}
		}
	}
	cout << endl;
	return (varValue);
}

int read_random_discrete_value(int LBValue, int UBValue, int defaultValue, 
	int stepValue, bool *randValue)
{
	int varValue;
	string inputReader;
	int tempValue; //auxiliary value to count step values

	cout << "\nIt is possible to fix this value for all instances " <<
		"typing an integer value in {";

	tempValue = LBValue;
	while (tempValue < UBValue){
		cout << tempValue << ", ";
		tempValue += stepValue;
	}
	cout << UBValue << "}" <<
		".\nOtherwise press just enter for random values { " <<
		defaultValue << " }: ";

	cin.clear();
	getline(cin, inputReader);
	if (inputReader == "") {
		varValue = stepValue * rand_value(LBValue / stepValue, 
			UBValue / stepValue);
		*randValue = true;
		cout << varValue << endl;
	}
	else{
		if (!(is_digits(inputReader))) {
			varValue = stepValue * rand_value(LBValue / stepValue,
				UBValue / stepValue);
			*randValue = true;
			cout << "Wrong value, therefore random value is assumed: " <<
				"\n";
		}
		else{
			varValue = atoi(inputReader.c_str());;
			if (varValue < LBValue || varValue > UBValue){
				varValue = stepValue * rand_value(LBValue / stepValue,
					UBValue / stepValue);
				*randValue = true;
				cout << "The value exceeded the bounds, therefore a " <<
					"random value is assumed: " << "\n";
			}
		}
	}
	cout << endl;
	return (varValue);
}

int read_random_value(int LBValue, int UBValue, int defaultValue, 
	bool *randValue)
{
	int varValue;
	string inputReader;

	cout << "\nIt is possible to fix this value for all instances " <<
		"typing an integer value in [" << LBValue << "," << UBValue << "]" <<
		".\nOtherwise press just enter for random values { " <<
		defaultValue << " }: ";

	cin.clear();
	getline(cin, inputReader);
	if (inputReader == "") {
		varValue = rand_value(LBValue, UBValue);
		*randValue = true;
		cout << varValue << endl;
	}
	else{
		if (!(is_digits(inputReader))) {
			varValue = rand_value(LBValue, UBValue);
			*randValue = true;
			cout << "Wrong value, therefore random value is assumed: " <<
			"\n";
		}
		else{
			varValue = atoi(inputReader.c_str());;
			if (varValue < LBValue || varValue > UBValue){
				*randValue = true;
				varValue = rand_value(LBValue, UBValue);
				cout << "The value exceeded the bounds, therefore a " <<
					"random value is assumed: " << "\n";
			}
		}
	}
	cout << endl;
	return (varValue);
}


int main(int argc, char** argv){
	// Variables set to default values
	int year = 2004;		//year
	int month = 4;	        //month
	int day = 5;	        //day
	int periodsNumber = 24;	//number of periods
	int nOPT = 16;	        //number of o.p.
	int RVol = 2;	        //number of volumes
	int v_min_modif = 0;	//v_min modifier
	int v_max_modif = 0;	//v_max modifier
	int v_0_modif = 304;	//initial volume
	int v_T_modif = 304;	//target volume

	// Modifiers of the bounds according to previously selected data
	int month_LB_modif = 0; //modifier of the LB of the month
	int period_modif = 0;	//modifier of the UB of the periods
	
	// Boolean variables (false if the value is fixed, true otherwise)
	bool year_rand = false;
	bool month_rand = false;
	bool day_rand = false;
	bool periodsNumber_rand = false;
	bool nOPT_rand = false;
	bool RVol_rand = false;
	bool v_min_modif_rand = false;
	bool v_max_modif_rand = false;
	bool v_0_rand = false;
	bool v_T_rand = false;

	int status = 0;		    //result of the functions

	int instFormat = 0;		//format of the instances
	int instNumber = 1;	    //number of instances
	int outExtension = 1;	//extension of the file instances

	double totalInflows = 0.0; //sum over periods of the inflows

	double *prices;
	double *inflows;

	int aValue, bValue; //auxiliary variables to calculate bounds

	string inputReader;

	srand(time(0));

	//Printing information
	cout << "Istanceinator v0.99" << endl << endl;
	cout << "The generator of instances for the HUCP can be used in two";
	cout << " possible ways:" << endl;
	cout << "\t- Create a specific instance;" << endl;
	cout << "\t- Create some random instances." << endl << endl;
	cout << "In addition, three possible formats are available:\n";
	cout << "\t0 Single-reservoir instance format with one unique pair of "
		"volume bounds; " << endl;
	cout << "\t1 Multi-reservoir instance format." << endl << endl;
	/*cout << "\t2 Single-reserovir instance format with one pair of "
		"volume bounds per period; " << endl;*/

	//Selecting the format
	cout << "Please, select the format of instances you want to create.";
	instFormat = read_value(0, 1, instFormat);

	//Selecting the extenson of the file instances
	cout << "Please, select the extesion of the files to generate. "; 
	cout << "O .dat; 1 .dat .csv; 2.csv.";
	outExtension = read_value(0, 2, outExtension);

	//Selecting number of instances, i.e., genereting option
	cout << "Please, select the number of instances you want to create.";
	instNumber = read_value(1, 300, instNumber);

	//Genereting a unique specific instance
	if (instNumber == 1){

		cout << "Please, select the year of the starting date.";
		year = read_value(year_LB, year_UB, year);

		// Modifing the possible values of month according to the year 
		if (year == 2004)
			month_LB_modif = 3;

		cout << "Please, select the month of the starting date.";
		month = read_value(month_LB + month_LB_modif, month_UB, month);

		cout << "Please, select the day of the starting date.";
		day = read_value(day_LB, day_UB[month - 1] + is_leap_year(year, month),
			day);

		// Modifing the possible number of periods according to the date 
		if (year == year_UB){
			if (month == month_UB){
				if (day >= (day_UB[month - 1] - 6)){
					period_modif =  24 * (day_UB[month - 1] - day + 1)
						- periodsNumber_UB;
				}
			}
		}

		cout << "Please, select the number of periods.";
		periodsNumber = read_discrete_value(periodsNumber_LB, 
			periodsNumber_UB + period_modif, periodsNumber,24);

		cout << "Please, select the number of operational points "; 
		cout << "for turbines.";
		nOPT = read_value(nOPT_LB, nOPT_UB, nOPT);

		status = read_prices(year, month, day, periodsNumber, &prices);

		if (!status){
			//TODO
		}

		status = read_inflows(year, month, day, periodsNumber, &inflows,
			&totalInflows);
		if (!status){
			//TODO
		}

		cout << "Please, select the number of volume steps.";
		RVol = read_value(RVol_LB, RVol_UB, RVol);

		cout << "Please, select the modifier of the LB on the volume.";
		v_min_modif = read_value(v_min_modif_LB, v_min_modif_UB, v_min_modif);

		cout << "Please, select the modifier of the UB on the volume.";
		v_max_modif = read_value(v_max_modif_LB, v_max_modif_UB, v_max_modif);

		// Caluculating bounds on values of v_0
		v_0_modif_LB = ceil((v_min_modif*v_step) / (v_double_step + 0.0));
		v_0_modif_UB = floor((v_UB - v_LB - (v_max_modif*v_step)) 
			/ (v_double_step + 0.0));

		if (v_0_modif<v_0_modif_LB || v_0_modif_LB>v_0_modif_UB){
			v_0_modif = rand_value(v_0_modif_LB, v_0_modif_UB);
		}

		cout << "Please, select the initial volume.";
		v_0_modif = read_value(v_0_modif_LB, v_0_modif_UB, v_0_modif);

		// Caluculating bounds on values of v_T 
		aValue = ceil((v_min_modif*v_step) / (v_double_step + 0.0));
		bValue = v_0_modif + ceil((totalInflows - (periodsNumber * 21))
			* 3600 / (v_double_step + 0.0));
		v_T_modif_LB = max(aValue, bValue);
		aValue = floor((v_UB - v_LB - (v_max_modif*v_step))
			/ (v_double_step + 0.0));
		bValue = v_0_modif + floor((totalInflows + (periodsNumber * 13.49))
			* 3600 / (v_double_step + 0.0));
		v_T_modif_UB = min(aValue, bValue);

		if (v_T_modif<v_T_modif_LB || v_T_modif_LB>v_T_modif_UB){
			v_T_modif = rand_value(v_T_modif_LB, v_T_modif_UB);
		}

		cout << "Please, select the target volume.";
		v_T_modif = read_value(v_T_modif_LB, v_T_modif_UB, v_T_modif);

		cout << endl;
		if (outExtension < 2){
			status = write_instance(instFormat, year, month, day, 
				periodsNumber, nOPT, &prices, &inflows, RVol, v_0_modif, 
				v_T_modif, v_min_modif, v_max_modif);
		}
		if (outExtension > 0){
			status = write_csv_instance(instFormat, year, month, day, 
				periodsNumber, nOPT, &prices, &inflows, RVol, v_0_modif, 
				v_T_modif, v_min_modif, v_max_modif);
		}
		if (!status){
			//TODO
		}

		delete[] prices;
		delete[] inflows;
	}
	else{
		//Genereting n random instances
		cout << "Please, select the year of the starting date.";
		year = read_random_value(year_LB, year_UB, year, &year_rand);

		// Modifing the possible values of month according to the year
		if (year == 2004)
			month_LB_modif = 3;
		else
			month_LB_modif = 0;

		cout << "Please, select the month of the starting date.";
		month = read_random_value(month_LB + month_LB_modif, month_UB, month, 
			&month_rand);

		cout << "Please, select the day of the starting date.";
		day = read_random_value(day_LB,
			day_UB[month - 1] + is_leap_year(year, month), day, &day_rand);

		// Modifing the possible number of periods according to the date
		period_modif = 0;
		if (year == year_UB){
			if (month == month_UB){
				if (day >= (day_UB[month - 1] - 6)){
					period_modif = 24 * (day_UB[month - 1] - day + 1)
						- periodsNumber_UB;
				}
			}
		}

		cout << "Please, select the number of periods.";
		periodsNumber = read_random_discrete_value(periodsNumber_LB, 
			periodsNumber_UB + period_modif, periodsNumber, 24, 
			&periodsNumber_rand);

		cout << "Please, select the number of operational points ";
		cout << "for turbines.";
		nOPT = read_random_value(nOPT_LB, nOPT_UB, nOPT, &nOPT_rand);

		status = read_prices(year, month, day, periodsNumber, &prices);

		if (!status){
			//TODO
		}

		status = read_inflows(year, month, day, periodsNumber, &inflows,
			&totalInflows);
		if (!status){
			//TODO
		}

		cout << "Please, select the number of volume steps.";
		RVol = read_random_value(RVol_LB, RVol_UB, RVol, &RVol_rand);

		cout << "Please, select the modifier of the LB on the volume.";
		v_min_modif = read_random_value(v_min_modif_LB, v_min_modif_UB,
			v_min_modif, &v_min_modif_rand);

		cout << "Please, select the modifier of the UB on the volume.";
		v_max_modif = read_random_value(v_max_modif_LB, v_max_modif_UB,
			v_max_modif, &v_max_modif_rand);

		// Caluculating bounds on values of v_0 and v_T 
		v_0_modif_LB = ceil((v_min_modif*v_step) / (v_double_step + 0.0));
		v_0_modif_UB = floor((v_UB - v_LB - (v_max_modif*v_step))
			/ (v_double_step + 0.0));

		cout << "Please, select the initial volume.";
		v_0_modif = read_random_value(v_0_modif_LB, v_0_modif_UB, v_0_modif,
			&v_0_rand);

		// Caluculating bounds on values of v_T 
		aValue = ceil((v_min_modif*v_step) / (v_double_step + 0.0));
		bValue = v_0_modif + ceil((totalInflows - (periodsNumber * 21))
			* 3600 / (v_double_step + 0.0));
		v_T_modif_LB = max(aValue, bValue);
		aValue = floor((v_UB - v_LB - (v_max_modif*v_step))
			/ (v_double_step + 0.0));
		bValue = v_0_modif + floor((totalInflows + (periodsNumber * 13.49))
			* 3600 / (v_double_step + 0.0));
		v_T_modif_UB = min(aValue, bValue);

		cout << "Please, select the target volume.";
		v_T_modif = read_random_value(v_T_modif_LB, v_T_modif_UB, v_T_modif,
			&v_T_rand);

		cout << endl;

		if (outExtension < 2){
			status = write_instance(instFormat, year, month, day,
				periodsNumber, nOPT, &prices, &inflows, RVol, v_0_modif,
				v_T_modif, v_min_modif, v_max_modif);
		}
		if (outExtension > 0){
			status = write_csv_instance(instFormat, year, month, day, 
				periodsNumber, nOPT, &prices, &inflows, RVol, v_0_modif, 
				v_T_modif, v_min_modif, v_max_modif);
		}
		if (!status){
			//TODO
		}

		delete[] prices;
		delete[] inflows;

		for (int i = 1; i < instNumber; i++){
			if (year_rand == true)
				year = rand_value(year_LB, year_UB);
			
			// Modifing the possible values of month according to the year
			if (year == 2004)
				month_LB_modif = 3;
			else
				month_LB_modif = 0;

			if (month_rand == true)
				month = rand_value(month_LB + month_LB_modif, month_UB);

			if (day_rand == true)
				day = rand_value(day_LB, day_UB[month - 1] +
					is_leap_year(year, month));

			// Modifing the possible number of periods according to the date
			period_modif = 0;
			if (year == year_UB){
				if (month == month_UB){
					if (day >= (day_UB[month - 1] - 6)){
						period_modif = 24 * (day_UB[month - 1] - day + 1)
							- periodsNumber_UB;
					}
				}
			}

			if (periodsNumber_rand == true)
				periodsNumber = rand_value(periodsNumber_LB, 
					periodsNumber_UB + period_modif);

			if (nOPT_rand == true)
				nOPT = rand_value(nOPT_LB, nOPT_UB);

			status = read_prices(year, month, day, periodsNumber, &prices);

			if (!status){
				//TODO
			}

			status = read_inflows(year, month, day, periodsNumber, &inflows,
				&totalInflows);
			if (!status){
				//TODO
			}

			if (RVol_rand == true)
				RVol = rand_value(RVol_LB, RVol_UB);

			if (v_min_modif_rand == true)
				v_min_modif = rand_value(v_min_modif_LB, v_min_modif_UB);
			if (v_max_modif_rand == true)
				v_max_modif = rand_value(v_max_modif_LB, v_max_modif_UB);
			
			// Caluculating bounds on values of v_0 and v_T 
			v_0_modif_LB = ceil((v_min_modif*v_step) / (v_double_step + 0.0));
			v_0_modif_UB = floor((v_UB - v_LB - (v_max_modif*v_step))
				/ (v_double_step + 0.0));

			if (v_0_rand == true)
				v_0_modif = rand_value(v_0_modif_LB, v_0_modif_UB);

			// Caluculating bounds on values of v_T 
			aValue = ceil((v_min_modif*v_step) / (v_double_step + 0.0));
			bValue = v_0_modif + ceil((totalInflows - (periodsNumber * 21))
				* 3600 / (v_double_step + 0.0));
			v_T_modif_LB = max(aValue, bValue);
			aValue = floor((v_UB - v_LB - (v_max_modif*v_step))
				/ (v_double_step + 0.0));
			bValue = v_0_modif + floor((totalInflows + (periodsNumber * 13.49))
				* 3600 / (v_double_step + 0.0));
			v_T_modif_UB = min(aValue, bValue);

			if (v_T_rand == true)
				v_T_modif = rand_value(v_T_modif_LB, v_T_modif_UB);

			if (outExtension < 2){
				status = write_instance(instFormat, year, month, day,
					periodsNumber, nOPT, &prices, &inflows, RVol, v_0_modif,
					v_T_modif, v_min_modif, v_max_modif);
			}
			if (outExtension > 0){
				status = write_csv_instance(instFormat, year, month, day,
					periodsNumber, nOPT, &prices, &inflows, RVol, v_0_modif,
					v_T_modif, v_min_modif, v_max_modif);
			}
			if (!status){
				//TODO
			}

			delete[] prices;
			delete[] inflows;

		}

	}

	return 0;
}