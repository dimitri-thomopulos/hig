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

/* @file     :head.h
 * @brief    :Main header linking all files
 * @author   :Dimitri Thomopulos
 * @date     :20180730
 * @version  :1.00
 */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MAIN_HEADER
#define MAIN_HEADER

#define INFINITY 99999999999
#define EPSYLON 0.0000001

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <errno.h>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <complex>
#include <iomanip>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>

#include "read.h"
#include "write_instance.h"

#define MAX_RESERVOIR 4
#define MAX_TURBINES 5

int const v_LB[MAX_RESERVOIR] = { 38400000, 2500000, 100000, 15000000 };
int const v_UB[MAX_RESERVOIR] = { 84400000, 5500000, 200000, 33000000 };
int const v_step = 10000;
int const v_double_step = 20000;

int is_leap_year(int year, int month);

#endif
