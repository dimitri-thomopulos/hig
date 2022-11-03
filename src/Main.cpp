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
 * @version  :1.04
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

double const min_qiValues[5] = { 0.5, 21, 1.4, 8.4, 0.1 };
double const max_qiValues[5] = { 2.8, 104.6, 7, 42, 0.3 };

double const min_quValues[2] = { 0, 0 };
double const max_quValues[2] = { -67.19, -26.98 };

int const t2Up[5] = {  1,  1,  2,  4,  3 };
int const t2p[5]  = { -1,  1, -1,  2, -1 };


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

double calculate_max_pump(const double *max_quValues, const int *t2Up, 
	const int*t2p, int res ){
	double q_max = 0;
	for (int t = 0; t < 5; t++){
		if (t2Up[t] == res){
			if (t2p[t] >= 0){
				q_max += max_quValues[t2p[t] - 1];
			}
		}
	}
	return(q_max);
}

int read_set_discrete_value(int LBValue, int UBValue, int defaultValue, 
	int stepValue, char *text)
{
	int varValue;
	string inputReader;
	int tempValue; //auxiliary value to count step values

	cout << text;
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

int read_set_value(int LBValue, int UBValue, int defaultValue, char *text)
{
	int varValue;
	string inputReader;

	cout << text;
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

int read_array_set_value(int *LBValue, int *UBValue, int **defaultValue, 
	int array_size, char *text)
{
	int* varValue = new int[array_size];
	string inputReader;

	cout << text;
	if (array_size > 1){
		cout << "\n" << array_size << " inputs are required.";
	}
	for (int i = 0; i < array_size; i++){
		cout << "\nAn integer value for input "<< i + 1 << " in [" << 
			LBValue[i] << "," << UBValue[i] << "]" <<
			" is required. Press enter for the default value { " <<
			(*defaultValue)[i] << " }: ";

		cin.clear();
		getline(cin, inputReader);
		if (inputReader == "") {
			varValue[i] = (*defaultValue)[i];
			cout << "Default value: " << varValue[i] << "\n";
			for (int j = i + 1; j < array_size; j++){
				varValue[j] = (*defaultValue)[j];
				cout << "Input " << j  + 1 << " set to default value: " << 
					varValue[j] << "\n";
			}
			break;
		}
		else{
			if (!(is_digits(inputReader))) {
				varValue[i] = (*defaultValue)[i];
				cout << "Wrong value, therefore the default value" <<
					" is assumed: " << varValue[i] << "\n";
			}
			else{
				varValue[i] = atoi(inputReader.c_str());
				(*defaultValue)[i] = varValue[i];
				if (varValue[i] < LBValue[i] || varValue[i] > UBValue[i]){
					varValue[i] = (*defaultValue)[i];
					cout << "The value exceeded the bounds, therefore the " <<
						"default value is assumed: " << varValue[i] << "\n";
				}
			}
		}
	}
	cout << endl;
	return (0);
}

int read_random_discrete_value(int LBValue, int UBValue, int defaultValue, 
	int stepValue, bool *randValue, int instanceId, char *text)
{
	int varValue;
	string inputReader;
	int tempValue; //auxiliary value to count step values

	if (instanceId > 1){
		if (*randValue == true){
			varValue = stepValue * rand_value(LBValue / stepValue,
				UBValue / stepValue);
			return (varValue);
		}
		else{
			return (defaultValue);
		}
	}
	else
	{
		cout << text;
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
	}
	cout << endl;
	return (varValue);
}

int read_random_value(int LBValue, int UBValue, int defaultValue, 
	bool *randValue, int instanceId, char *text)
{
	int varValue;
	string inputReader;

	if (instanceId > 1){
		if (*randValue == true){
			varValue = rand_value(LBValue, UBValue);
			return (varValue);
		}
		else{
			return (defaultValue);
		}
	}
	else
	{
		cout << text;
		cout << "\nIt is possible to fix this value for all instances " <<
			"typing an integer value in [" << LBValue << "," << UBValue <<
			"]" << ".\nOtherwise press just enter for random values { " <<
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
	}
	return (varValue);
}

int read_array_random_value(int *LBValue, int *UBValue, int **defaultValue,
	int array_size, bool **randValue, int instanceId, char *text)
{
	int* varValue = new int[array_size];
	string inputReader;
	bool toRandom = false; // auxiliary variable 
						   // (true if not all values are random) 
	
	if (instanceId > 1){
		for (int i = 0; i < array_size; i++){
			if (*randValue[i] == true){
				(*defaultValue)[i] = rand_value(LBValue[i], UBValue[i]);
			}
		}
		return (0);
	}
	else
	{
		cout << text;
		if (array_size > 1){
			cout << "\n" << array_size << " inputs are required. " << 
				"It is possible to fix all or some of these values for all " <<
				"instances typing 1 now." << 
				"\nOtherwise press just enter for all random values";
			cin.clear();
			getline(cin, inputReader);
			if (inputReader == "1") {
				toRandom = false;
			}
			else
			{ 
				toRandom = true; 
			}
		}
		for (int i = 0; i < array_size; i++){
			if (toRandom == true){
				(*defaultValue)[i] = rand_value(LBValue[i], UBValue[i]);
			}
			else{
				cout << "\nAn integer value for input " << i + 1 << " in [" <<
					LBValue[i] << "," << UBValue[i] << "]" <<
					" is required. Press enter for random values { " <<
					(*defaultValue)[i] << " }: ";

				cin.clear();
				getline(cin, inputReader);
				if (inputReader == "") {
					(*defaultValue)[i] = rand_value(LBValue[i], UBValue[i]);
					(*randValue)[i] = true;
					cout << (*defaultValue)[i] << endl;
				}
				else{
					if (!(is_digits(inputReader))) {
						(*defaultValue)[i] = 
							rand_value(LBValue[i], UBValue[i]);
						(*randValue)[i] = true;
						cout << "Wrong value, therefore random value" <<
							" is assumed: " << "\n";
					}
					else{
						varValue[i] = atoi(inputReader.c_str());
						(*defaultValue)[i] = varValue[i];
						if (varValue[i] < LBValue[i] || 
							varValue[i] > UBValue[i]){
							(*randValue)[i] = true;
							(*defaultValue)[i] = 
								rand_value(LBValue[i], UBValue[i]);
							cout << "The value exceeded the bounds, " <<
								"therefore a random value is assumed: " << 
								varValue[i] << "\n";
						}
					}
				}
			}
		}
	}
	cout << endl;
	return (0);
}

int read_discrete_value(int LBValue, int UBValue, int defaultValue, 
	int stepValue, bool *randValue, int instanceId, 
	int instNumber, char *text)
{
	int varValue;
	if (instNumber == 1){
		varValue = read_set_discrete_value(LBValue, UBValue, defaultValue, 
			stepValue, text);
	}
	else{
		varValue = read_random_discrete_value(LBValue, UBValue, defaultValue, 
			stepValue, randValue, instanceId, text);
	}
	return (varValue);
}

int read_value(int LBValue, int UBValue, int defaultValue,
	bool *randValue, int instanceId, int instNumber,
	char *text)
{
	int varValue;
	if (instNumber == 1){
		varValue = read_set_value(LBValue, UBValue, defaultValue, text);
	}
	else{
		varValue = read_random_value(LBValue, UBValue, defaultValue, 
			randValue, instanceId, text);
	}
	return (varValue);
}

int read_array_value(int *LBValue, int *UBValue, int **defaultValue,
	bool **randValue, int instanceId, int array_size, int instNumber, 
	char *text)
{
	int varValue = 0;
	if (instNumber == 1){
		varValue = read_array_set_value(LBValue, UBValue, defaultValue, 
			array_size, text);
	}
	else{
		varValue = read_array_random_value(LBValue, UBValue, defaultValue,
			array_size, randValue, instanceId, text);
	}
	return (varValue);
}


int calculate_v_0_bounds(int **v_0_modif_LB, int **v_0_modif_UB, 
	int v_min_modif, int v_max_modif, const int *v_LB, const int *v_UB, 
	int step, int double_step, int res, int instFormat)
{
	int f_res;
	if (instFormat != 2){
		f_res = 3;
	}
	else{
		f_res = res;
	}
	(*v_0_modif_LB)[res] = ceil((v_min_modif*step) / (double_step + 0.0));
	(*v_0_modif_UB)[res] = floor((v_UB[f_res] - v_LB[f_res] - 
		(v_max_modif*step)) / (double_step + 0.0));
	return (0);
}

int calculate_v_T_bounds(int **v_T_modif_LB, int **v_T_modif_UB,
	int v_min_modif, int v_max_modif, int v_0_modif, const int *v_LB, 
	const int *v_UB, int periodsNumber, double totalInflows,
	const double *max_qiValues, const double *max_quValues,
	const int *t2Up, const int*t2p,
	int step, int double_step, int res, int instFormat)
{
	int f_res;
	int aValue, bValue; //auxiliary variables to calculate bounds
	if (instFormat != 2){
		f_res = 3;
	}
	else{
		f_res = res;
	}
	double max_quValue = calculate_max_pump(max_quValues, t2Up, t2p, 
		f_res + 1); //max pump flow value

	aValue = ceil((v_min_modif*step) / (double_step + 0.0));
	bValue = v_0_modif
		+ ceil((totalInflows - (periodsNumber * (max_qiValues[f_res] / 2)))
		* 3600 / (double_step + 0.0));
	(*v_T_modif_LB)[res] = max(aValue, bValue);
	aValue = floor((v_UB[f_res] - v_LB[f_res] - (v_max_modif*step))
		/ (double_step + 0.0));
	bValue = v_0_modif
		+ floor((totalInflows +
		(periodsNumber * (-max_quValue / 2)))
		* 3600 / (double_step + 0.0));
	(*v_T_modif_UB)[res] = min(aValue, bValue);
	return (0);
}

int main(int argc, char** argv){
	// Variables set to default values
	int year = 2004;		//year
	int month = 4;			//month
	int day = 5;			//day
	int periodsNumber = 168;	//number of periods//24
	int nOPT = 35;			//number of o.p.//16
	int RVol = 5;			//number of volumes//2
	int* v_min_modif;	//v_min modifier//0
	int* v_max_modif;	//v_max modifier//0
	int* v_0_modif;	//initial volume//304
	int* v_T_modif;	//target volume//304
	// array of bounds of volume modifiers
	int* v_min_modif_LB;
	int* v_min_modif_UB;
	int* v_max_modif_LB;
	int* v_max_modif_UB;
	int* v_0_modif_LB;
	int* v_0_modif_UB;
	int* v_T_modif_LB;
	int* v_T_modif_UB;
	
	//index of the turbine/plant to use for the single reservoir case
	int one_res = 3;

	//min and max value of the min volume for single reservoir case
	int v_min_LB = v_LB[one_res];
	int v_min_UB = (v_UB[one_res] + v_LB[one_res]) / 2;
	//min and max value of the max volume for single reservoir case
	int v_max_LB = (v_UB[one_res] + v_LB[one_res]) / 2;
	int v_max_UB = v_UB[one_res];

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
	bool *v_min_modif_rand;
	bool *v_max_modif_rand;
	bool *v_0_modif_rand;
	bool *v_T_modif_rand;

	int status = 0;		    //result of the functions

	int instFormat = 0;		//format of the instances
	int instNumber = 1;	    //number of instances
	int outExtension = 1;	//extension of the file instances

	double totalInflows = 0.0; //sum over periods of the inflows

	double *prices;
	double *inflows;

	int res_number = 1; // number of reservoirs
	int turb_number = 1; // number of turbines

	char v_text[200]; //auxiliary "string" for terminal/promt output
						//about volume modifiers

	string inputReader;

	srand(time(0));

	//Printing information
	cout << "Istanceinator v1.04" << endl << endl;
	cout << "The generator of instances for the HUCP can be used in two";
	cout << " possible ways:" << endl;
	cout << "\t- Create a specific instance;" << endl;
	cout << "\t- Create some random instances." << endl << endl;
	cout << "In addition, three possible formats are available:\n";
	cout << "\t0 Single-reservoir instance format with one unique pair of "
		"volume bounds; " << endl;
	cout << "\t1 Single-reservoir in Multi-reservoir instance format." << endl;
	cout << "\t2 Multi-reservoir instance format." << endl << endl;
	/*cout << "\t3 Single-reserovir instance format with one pair of "
		"volume bounds per period; " << endl;*/

	//Selecting the format
	instFormat = read_set_value(0, 2, instFormat, 
		"Please, select the format of instances you want to create.");
	//setting the number of reservoirs
	if (instFormat == 2){
		res_number = MAX_RESERVOIR;
		turb_number = MAX_TURBINES;
	}

	//Inizializing volume modifiers
	v_min_modif = (int*)malloc(res_number * sizeof(int));
	v_max_modif = (int*)malloc(res_number * sizeof(int));
	v_0_modif = (int*)malloc(res_number * sizeof(int));
	v_T_modif = (int*)malloc(res_number * sizeof(int));

	v_min_modif_LB = (int*)malloc(res_number * sizeof(int));
	v_min_modif_UB = (int*)malloc(res_number * sizeof(int));
	v_max_modif_LB = (int*)malloc(res_number * sizeof(int));
	v_max_modif_UB = (int*)malloc(res_number * sizeof(int));
	v_0_modif_LB = (int*)malloc(res_number * sizeof(int));
	v_0_modif_UB = (int*)malloc(res_number * sizeof(int));
	v_T_modif_LB = (int*)malloc(res_number * sizeof(int));
	v_T_modif_UB = (int*)malloc(res_number * sizeof(int));

	v_min_modif_rand = (bool*)malloc(res_number * sizeof(bool));
	v_max_modif_rand = (bool*)malloc(res_number * sizeof(bool));
	v_0_modif_rand = (bool*)malloc(res_number * sizeof(bool));
	v_T_modif_rand = (bool*)malloc(res_number * sizeof(bool));

	for (int t = 0; t < res_number; t++){
		if (instFormat != 2){
			v_min_modif[t] = 0;
			v_max_modif[t] = 0;
			v_0_modif[t] = 304;
			v_T_modif[t] = 304;

			v_min_modif_LB[t] = 0;
			v_min_modif_UB[t] = 900;
			v_max_modif_LB[t] = 0;
			v_max_modif_UB[t] = 900;
			v_0_modif_LB[t] = 0;
			v_0_modif_UB[t] = 900;
			v_T_modif_LB[t] = 0;
			v_T_modif_UB[t] = 900;
		}
		else{
			v_min_modif[t] = 0;
			v_max_modif[t] = 0;
			v_0_modif[t] = 3;
			v_T_modif[t] = 3;

			v_min_modif_LB[t] = 0;
			v_min_modif_UB[t] = 9;
			v_max_modif_LB[t] = 0;
			v_max_modif_UB[t] = 9;
			v_0_modif_LB[t] = 0;
			v_0_modif_UB[t] = 9;
			v_T_modif_LB[t] = 0;
			v_T_modif_UB[t] = 9;
		}
			v_min_modif_rand[t] = false;
			v_max_modif_rand[t] = false;
			v_0_modif_rand[t] = false;
			v_T_modif_rand[t] = false;
	}
	

	//Selecting the extenson of the file instances
	cout << "0 .dat; 1 .dat .csv; 2.csv.";
	outExtension = read_set_value(0, 2, outExtension, 
		"Please, select the extesion of the files to generate. ");

	//Selecting number of instances, i.e., generating option
	instNumber = read_set_value(1, 300, instNumber, 
		"Please, select the number of instances you want to create.");

	//Generating a unique specific instance
	//or
	//Generating n random instances

	for (int i = 0; i < instNumber; i++){
		/* year */
		year = read_value(year_LB, year_UB, year, &year_rand, 
			i + 1, instNumber,
			"Please, select the year of the starting date.");

		/* month */
		// Modifing the possible values of month according to the year
		if (year == 2004)
			month_LB_modif = 3;
		else
			month_LB_modif = 0;

		month = read_value(month_LB + month_LB_modif, month_UB, 
			month, &month_rand, i + 1, instNumber, 
			"Please, select the month of the starting date.");

		/* day */
		day = read_value(day_LB,
			day_UB[month - 1] + is_leap_year(year, month), day, &day_rand, 
			i + 1, instNumber, 
			"Please, select the day of the starting date.");

		/* period */
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

		periodsNumber = read_discrete_value(periodsNumber_LB,
			periodsNumber_UB + period_modif, periodsNumber, 24,
			&periodsNumber_rand, i + 1, instNumber,
			"Please, select the number of periods.");

		/* nOPT */
		nOPT = read_value(nOPT_LB, nOPT_UB, nOPT, &nOPT_rand, 
			i + 1, instNumber,
			"Please, select the number of operational points for turbines."
			);

		/* reading Prices */
		status = read_prices(year, month, day, periodsNumber, &prices);

		if (!status){
			//TODO
		}

		/* reading Inflows */
		status = read_inflows(year, month, day, periodsNumber, &inflows,
			&totalInflows);
		if (!status){
			//TODO
		}

		/* R */
		RVol = read_value(RVol_LB, RVol_UB, RVol, &RVol_rand, 
			i + 1, instNumber,
			"Please, select the number of volume steps.");
		
		/* v_min modifiers */
		sprintf(v_text, "%s",
			"Please, select the modifier of the LB on the volume");
		if (instFormat != 2){
			sprintf(v_text, "%s%s", v_text, ".");
		}
		else{
			sprintf(v_text, "%s%s", v_text, " for every resevoir.");
		}
		status = read_array_value(v_min_modif_LB, v_min_modif_UB,
			&v_min_modif, &v_min_modif_rand, i + 1, res_number,
			instNumber,
			v_text);

		/* v_max modifiers */
		sprintf(v_text, "%s", 
			"Please, select the modifier of the UB on the volume");
		if (instFormat != 2){
			sprintf(v_text, "%s%s", v_text, ".");
		}
		else{
			sprintf(v_text, "%s%s", v_text, " for every resevoir.");
		}
		status = read_array_value(v_max_modif_LB, v_max_modif_UB,
			&v_max_modif, &v_max_modif_rand, i + 1, res_number,
			instNumber,
			v_text);
		
		/* v_0 modifiers */
		// Calculating bounds on values of v_0
		for (int r = 0; r < res_number; r++){
			status = calculate_v_0_bounds(&v_0_modif_LB, &v_0_modif_UB, 
				v_min_modif[0], v_max_modif[0], v_LB, v_UB, v_step, 
				v_double_step, r, instFormat);
		}

		sprintf(v_text, "%s",
			"Please, select the initial volume");
		if (instFormat != 2){
			sprintf(v_text, "%s%s", v_text, ".");
		}
		else{
			sprintf(v_text, "%s%s", v_text, " for every resevoir.");
		}
		status = read_array_value(v_0_modif_LB, v_0_modif_UB,
			&v_0_modif, &v_0_modif_rand, i + 1, res_number,
			instNumber,
			v_text);

		/* v_T modifiers */
		// Calculating bounds on values of v_T
		for (int r = 0; r < res_number; r++){
			status = calculate_v_T_bounds(&v_T_modif_LB, &v_T_modif_UB,
				v_min_modif[0], v_max_modif[0], v_0_modif[0], v_LB, v_UB,
				periodsNumber, totalInflows, max_qiValues, max_quValues, t2Up,
				t2p, v_step, v_double_step, r, instFormat);
		}

		sprintf(v_text, "%s",
			"Please, select the target volume");
		if (instFormat != 2){
			sprintf(v_text, "%s%s", v_text, ".");
		}
		else{
			sprintf(v_text, "%s%s", v_text, " for every resevoir.");
		}
		status = read_array_value(v_T_modif_LB, v_T_modif_UB,
			&v_T_modif, &v_T_modif_rand, i + 1, res_number,
			instNumber,
			v_text);

		cout << endl;

		/* Writing instance */
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

	return 0;
}