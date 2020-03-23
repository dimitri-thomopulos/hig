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

/* @file     :read.cpp
 * @brief    :Functions for reading the data from the files
 * @author   :Dimitri Thomopulos
 * @date     :20180330
 * @version  :1.00
 */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "read.h"

using namespace std;

int const day_UB[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int read_prices(int year, int month, int day, int periodsNumber, 
	double **prices){

	int verbose = 1; // 1 to print percentage of done lines, 0 otherwise

	//Creating the string of the date
	int start_date = day + (month * 100) + (year *10000);

	*prices = new double[periodsNumber]; //memory allocation for prices

	int temp_data = 0; //auxiliary variable to count the dates

	//Reading the prices
	if (verbose == 1)
		cout << "*** Reading prices            ***" << endl;

	//Creating the name of the file containing data
	stringstream sStream;
	sStream << "Prices/Anno " << year << ".csv";
	string fileName = sStream.str();
	char priceFile[100];
	strcpy(priceFile, fileName.c_str());
	ifstream in(priceFile);
	sStream.str("");

	char* buf_ = new char[50];
	if (in.fail())
	{
		cout << "Instance reading ERROR" << endl << "Insert a value to end";
		int ir;
		cin >> ir;
		fstream err;
		err.open("Error.log", ios::app);
		err << "File could not be opened. " << endl;
		err.close();
		exit(-2);
	}

	//Reading data
	in.ignore(256, '\n'); //skip line
	in.ignore(256, '\n');
	//Searching for the first occurence
	while (temp_data < start_date && !in.eof()){
		in.ignore(256, '\n');
		in >> temp_data;
		if (!in) {
			cout << "*** Error -2 the date you selected is not available ***";
			cout << endl;
			return -2;
		}
		in.ignore(256, ';');
	}

	if (temp_data != start_date){
		cout << "*** Error -1 the date you selected is not available ***";
		cout << endl;
		return -1;
	}

	//Collecting data
	in.ignore(256, ';');
	//in.ignore(256, ';');
	in >> (*prices)[0];
	//cout << temp_data << "\t" << 0 + 1 << "\t" << (*prices)[0] << endl;
	if (verbose == 1)
		cout << "*** [";

	for (int i = 1; i < periodsNumber; i++){
		in.ignore(256, '\n');
		in >> temp_data;
		in.ignore(256, ';');
		in.ignore(256, ';');
		in >> (*prices)[i];
		//cout << temp_data << "\t" << i + 1 << "\t" << (*prices)[i] << endl;
		if (int(i * 19 / periodsNumber) != int((i - 1) * 19 / periodsNumber) && (verbose == 1)){
			cout << "=";
		}
	}
	if (verbose == 1)
		cout << "] 100% ***\n";

	delete[] buf_;

	cout << "*** Reading prices - Complete ***" << endl << endl;

	return 0;
}

int read_inflows(int year, int month, int day, int periodsNumber, 
	double **inflows, double *totalInflows){

	int verbose = 1; // 1 to print percentage of done lines, 0 otherwise

	//Creating the string of the date
	stringstream sStream;
	if (month < 10){
		sStream << year << "-0" << month;
	}
	else{
		sStream << year << "-" << month;
	}
	if (day < 10){
		sStream << "-0" << day;
	}
	else{
		sStream << "-" << day;
	}
	string start_date = sStream.str();
	sStream.str("");

	*inflows = new double[periodsNumber]; //memory allocation for inflows

	string temp_data; //auxiliary variable to count the dates

	//Reading the inflows
	if (verbose == 1)
		cout << "*** Reading inflows            ***" << endl;

	string fileName = "Inflows/Suviana_2004_2012.csv";
	char inflowFile[100];
	strcpy(inflowFile, fileName.c_str());
	ifstream in(inflowFile);

	char* buf_ = new char[50];
	if (in.fail())
	{
		cout << "Instance reading ERROR" << endl << "Insert a value to end";
		int ir;
		cin >> ir;
		fstream err;
		err.open("Error.log", ios::app);
		err << "File could not be opened. " << endl;
		err.close();
		exit(-3);
	}

	//Reading data
	//Searching for the first occurence
	while ((temp_data.compare(start_date) < 0) && !in.eof()){
		in.ignore(256, '\n');
		in >> temp_data;
		if (!in) {
			cout << "*** Error -12 the date you selected is not available ***";
			cout << endl;
			return -12;
		}
		in.ignore(256, ';');
	}

	if (temp_data != start_date){
		cout << "*** Error -11 the date you selected is not available ***";
		cout << endl;
		return -11;
	}

	//Collecting data
	in >> (*inflows)[0];
	//cout << temp_data << "\t" << 0 + 1 << "\t" << (*inflows)[0] << endl;
	if (verbose == 1)
		cout << "*** [";

	for (int i = 1; i < periodsNumber; i++){
		in.ignore(256, '\n');
		in >> temp_data;
		in.ignore(256, ';');
		in >> (*inflows)[i];
		(*totalInflows) += (*inflows)[i];
		//cout << temp_data << "\t" << i + 1 << "\t" << (*inflows)[i] << endl;
		if (int(i * 20 / periodsNumber) != int((i - 1) * 20 / periodsNumber) && (verbose == 1)){
			cout << "=";
		}
	}
	if (verbose == 1)
		cout << "] 100% ***\n";

	delete[] buf_;

	cout << "*** Reading inflows - Complete ***" << endl << endl;

	return 0;
}
