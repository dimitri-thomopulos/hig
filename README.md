# HIG
 HUCP Instances Generator (HIG) is a generator of instances for the Hydro Unit Commitement Problem.

## External requirements
The generator requires some data about prices from 
http://www.mercatoelettrico.org/.
A bash script is available among the provided files in order to download 
authomatically 
and in the right forlder the files with price data (An equivalent batch script 
for Windows will soon be available). It is sufficient to execute it, however 
the Users should convert the excel files into semicolon separated CSV files.
The necessary spreadsheet is "Prezzi-Prices". However, we remind you to accept the [terms of use of http://www.mercatoelettrico.org/](https://www.mercatoelettrico.org/En/Tools/Accessodati.aspx?ReturnUrl=%2fEn%2fDownload%2fDownloadDati.aspx%3fval%3dMGP_Prezzi&val=MGP_Prezzi).

The price data format that the generator needs to generate the instances is a separate csv file for each year that user wants to use called “Anno YYYY.csv" where YYYY is the year in question, for example, “Anno 2004.csv". An example csv (with ";" as separator) is

| Date (YYYYMMDD)| Hour | PUN |
|:----------|:-------:|:----------|
| 20040401 | 1 | 17.45 |
| 20040401 | 2 | 23.55 |
| 20040401 | 3 | 32.65 |

In the table are represented only the first 3 periods that in the case of the Italian electricity market correspond to one hour each. The first column includes the date in year, month, day format, i.e., YYYYMMDD. The second column indicates the reference time (between 1 and 24). Finally, the third column shows the national unit price (PUN) in €/MWh. The already downloadable files contain additional columns containing the market prices of individual zones and neighboring markets. However, these values are not used explicitly by the generator.

## Installation
To install the genearator on any Linux O.S. it is sufficient to run " make ".
Then to execute it is sufficient to run " ./HIG " and follow the instructions.

Instructions for Linux O.S.:

	1 Execute "chmod +x getPrices.sh"
	
	2 Execute "./getPrices.sh" ;
	
	3 Convert the .xls files in semicolon separated .csv files
	
	4 Execute "make"
	
	5 Execute "./HIG"
	
	6 Enjoy creating instances
