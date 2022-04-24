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

/* @file     :write_instance.h
 * @brief    :Functions for writing the instances
 * @author   :Dimitri Thomopulos
 * @date     :20180730
 * @version  :1.00
 */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef WRITE_INSTANCE_HEAD
#define WRITE_INSTANCE_HEAD
#include "head.h"

int write_instance(int instFormat, int year, int month, int day,
	int periodsNumber, int nOPT, double **prices, double **inflows, int RVol,
	int v_0_modif, int v_T_modif, int v_min_modif, int v_max_modif); 
	//function to write instances in .dat extension files

int write_csv_instance(int instFormat, int year, int month, int day,
	int periodsNumber, int nOPT, double **prices, double **inflows, int RVol,
	int v_0_modif, int v_T_modif, int v_min_modif, int v_max_modif);
	//function to write instances in .csv extension files

#endif
