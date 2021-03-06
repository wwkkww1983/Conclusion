#ifndef __DECOTROLLERDESIGN_H
#define __DECOTROLLERDESIGN_H

#include "stm32f10x.h"
#include "stm32f10_timer.h"
#include "analogin.h"
#include "stm32f10_dac.h"
#include "stm32f10_gpio.h"	
#include <math.h>  
#include <stdio.h>

#define DESTVALUE             1	//     继电器启动
#define DESPVALUE			  0	//     继电器停止

// preset value

#define DEWFLOWMIN            1  //    循环流体流速下限
#define DEWTIM                1800  // 溶液加热等待时间上限
#define DESTEMPSP             21 //   溶液工作区适合温度
#define DEPUMPSP              40   //  泵的初始化默认频率
#define DEFANSP               40   //  风机的初始化默认频率
#define DESDENSITY            30//	   盐溶液浓度
#define DESTEMAX              24 //   溶液工作区适合温度
#define	DEMINSOLTEM		      7
#define FR_VAL	              40 //flowrate adjustment basic value
#define FR_STEP_VAL	           2 //flowrate adjustment step value
#define HAL_FR_STEP_VAL		   1.5

#define  FR_ACCRCY	           6   //followrate accuarcy  
#define  STRT_T_PUMP           1   //transfer pump start 
#define  DE_APP_LEVEL	       30 //appropriate liquid level

#define  STRT_SV4   	    1	 // open sv3 
#define  STRT_TO_PUMP   	1	 // optional pump replace sv3
										   
#define  HIGHLEVELAL	    1	   //highlevel alarm out put value DO = 1 
#define  DELIQMAX  	       45        	  //dehumidifer maximum liquid level
#define  DELIQMIN	       12     //dehumidifer minimum liquid level

#define  TEMPMIN	        8   // adjustment temperature threshold
#define  FLOWMAX		   43  // adjustment flowrate threshold

#define  ST_APP_LEVEL	  30	   //strong solution tank	approprated level
#define  DT_APP_LEVEL	  30     //diluted solution tank approprated level

/***************IO port lab*****************************/
 //AI
#define   FLOW                0
#define   PUMPFB              1
#define   FANFB               2
#define   CSFB                3
#define   CONDFB              4
#define   INLET_TEMP          5
#define   INLET_HUMIDITY      6
#define   OUTLET_TEMP         7
#define   OUTLET_HUMIDITY	  8
#define   LEVEL               9
#define   PRESSURE1           10
#define   PRESSURE3           11
#define   INSOLUTION_TEMP     12//t7
#define   p3                  13
#define   T5                  14
#define   OUTSOLUTION_TEMP    15
//DO
#define   DESTART 			   0
#define   FAUT_HIGHLEVEL	   1
#define   TRANFERPUMP          2
#define	  SV1				   3
#define	  SV4				   4
//DI
#define   LOCALORREMOTE        0
#define   FAUT_PUMP            1
#define   FAUT_FAN             2

//AO
#define   DE_PUMP 			  0
#define   DE_FAN		      1   
#define   DE_CS 			  2   

//Setpoint

#define   SETPUPDATE          0
#define   SETP_TEMPERATURE    2
#define	  SETP_HUMIDITY 	  1

//control 
#define LOWDENSITY	           0
#define MIDDENSITY			   1
#define HIGHDENSITY			   2

/******************************************************/
//IOport sinberbest
//AI
//
//#define   FLOW                2
//#define   PUMPFB              0
//#define   FANFB               1
//#define   INLET_TEMP          6
//#define   INLET_HUMIDITY      5
//#define   OUTLET_TEMP         4
//#define   OUTLET_HUMIDITY	  3
//#define   LEVEL               7
//#define   OUTSOLUTION_TEMP    9//t7
//
//#define   INSOLUTION_TEMP     8
//#define   HEXINLETSOL         10
//#define   HEXOUTLETSOL        11
//
//#define   DESTART 			  0
////DO
//#define   DEPUMPSTART 		  0
//#define   DEFUNSTART          1
//#define   TRANFERPUMP         2
//#define	  SV3				  3
////DI
//#define   LOCALORREMOTE       7
//#define   FAUT_PUMP           6
//#define   FAUT_FAN            5
//#define   FAUT_TRANPUMP       4
////AO
//#define   DE_PUMP 			  0
//#define   DE_FAN		      1     
////Setpoint
//#define   SETPUPDATE          0
//#define   SETP_TEMPERATURE    1
//#define	  SETP_HUMIDITY 	  2

#define 	 NEURALNUM   9

static float   con2dens[12][11] = {{1106.66, 1106.50, 1106.33, 1106.14, 1105.94, 1105.73, 1105.51, 1105.28, 1105.04, 1104.78, 1104.51  },
                                  {1113.00, 1112.84, 1112.67, 1112.48, 1112.29, 1112.07, 1111.85, 1111.62, 1111.37, 1111.12, 1110.85  }	,
                                  {1119.40, 1119.23, 1119.06, 1118.87, 1118.67, 1118.46, 1118.24, 1118.00, 1117.76, 1117.50, 1117.23 } ,
                                  {1125.83, 1125.67, 1125.50, 1125.31, 1125.11, 1124.90, 1124.67, 1124.43, 1124.19, 1123.93, 1123.66  },
                                  {1132.32, 1132.16, 1131.98, 1131.79, 1131.59, 1131.38, 1131.15, 1130.91, 1130.66, 1130.40, 1130.13  },
                                  {1138.86, 1138.69, 1138.52, 1138.33, 1138.12, 1137.91, 1137.68, 1137.44, 1137.19, 1136.93, 1136.65 }, 
                                  {1145.44, 1145.27, 1145.10, 1144.90, 1144.70, 1144.48, 1144.25, 1144.01, 1143.76, 1143.50, 1143.22 } ,
                                  {1152.07, 1151.90, 1151.72, 1151.53, 1151.33, 1151.11, 1150.88, 1150.63, 1150.38, 1150.11, 1149.84 }, 
                                  {1158.75, 1158.58, 1158.40, 1158.21, 1158.00, 1157.78, 1157.55, 1157.30, 1157.05, 1156.78, 1156.50  },
                                  {1165.47, 1165.31, 1165.12, 1164.93, 1164.72, 1164.50, 1164.27, 1164.02, 1163.77, 1163.50, 1163.22  },
                                  {1185.96, 1185.79, 1185.61, 1185.41, 1185.20, 1184.97, 1184.74, 1184.49, 1184.22, 1183.95, 1183.67  },
                                  {1199.89, 1199.72, 1199.53, 1199.33, 1199.12, 1198.89, 1198.65, 1198.40, 1198.13, 1197.86, 1197.57  },
								  }	;

//static float   hummatric17[12][7] ={ {7.20, 7.55, 7.92, 8.31, 8.72, 9.16, 9.63 },
//                                     {7.00, 7.33, 7.69, 8.07, 8.47, 8.89, 9.34 },
//                                     {6.79, 7.12, 7.46, 7.82, 8.21, 8.61, 9.04 },
//								       {6.58, 6.89, 7.22, 7.57, 7.93, 8.32, 8.74  },
//								       {6.37, 6.66, 6.97, 7.31, 7.66, 8.03, 8.42  },
//								       {6.15, 6.43, 6.72, 7.04, 7.37, 7.73, 8.10  },
//								       {5.92, 6.19, 6.47, 6.77, 7.09, 7.42, 7.78 },
//								       {5.70, 5.95, 6.22, 6.50, 6.80, 7.12, 7.46  },
//								       {5.48, 5.71, 5.96, 6.23, 6.51, 6.81, 7.13 },
//								       {5.26, 5.48, 5.71, 5.96, 6.23, 6.51, 6.81  },
//								       {4.62, 4.80, 4.99, 5.19, 5.41, 5.64, 5.88  },
//								       {4.23, 4.39, 4.55, 4.73, 4.91, 5.11, 5.31 },
//								 }	;
//
//static float hummatric11[12][7] ={ {6.36, 6.71, 7.08, 7.47, 7.89, 8.33, 8.79  },
//                                   {6.16, 6.50, 6.86, 7.23, 7.63, 8.06, 8.50  },
//                                   {5.96, 6.28, 6.62, 6.99, 7.37, 7.78, 8.21  },
//								   {5.75, 6.06, 6.38, 6.73, 7.10, 7.49, 7.90   },
//								   {5.53, 5.83, 6.14, 6.47, 6.82, 7.19, 7.59   },
//								   {5.31, 5.59, 5.89, 6.20, 6.54, 6.89, 7.27   },
//								   {5.09, 5.35, 5.64, 5.94, 6.25, 6.59, 6.95  },
//								   {4.86, 5.12, 5.38, 5.67, 5.97, 6.28, 6.62   },
//								   {4.64, 4.88, 5.13, 5.40, 5.68, 5.98, 6.30  },
//								   {4.42, 4.64, 4.88, 5.13, 5.39, 5.68, 5.97   },
//								   {3.79, 3.97, 4.16, 4.36, 4.57, 4.80, 5.05 },
//								   {3.40, 3.55, 3.72, 3.89, 4.07, 4.27, 4.48  },
//								 }	;
//
//static float hummatric14[12][7] ={ {6.77, 7.12, 7.49, 7.88, 8.29, 8.73, 9.20   },
//                                   {6.57, 6.90, 7.26, 7.64, 8.04, 8.46, 8.91   },
//                                   {6.36, 6.69, 7.03, 7.39, 7.78, 8.18, 8.61   },
//								   {6.15, 6.46, 6.79, 7.14, 7.50, 7.89, 8.31   },
//								   {5.94, 6.23, 6.54, 6.88, 7.23, 7.60, 7.99    },
//								   {5.72, 6.00, 6.29, 6.61, 6.94, 7.30, 7.67    },
//								   {5.49, 5.76, 6.04, 6.34, 6.66, 7.00, 7.35   },
//								   {5.27, 5.52, 5.79, 6.07, 6.37, 6.69, 7.03   },
//								   {5.05, 5.28, 5.53, 5.80, 6.08, 6.38, 6.70   },
//								   {4.83, 5.05, 5.28, 5.53, 5.80, 6.08, 6.38    },
//								   {4.19, 4.37, 4.56, 4.76, 4.98, 5.21, 5.45  },
//								   {3.80, 3.96, 4.12, 4.30, 4.48, 4.68, 4.88   },
//								 }	;



static float  hummatric17[18][17]={  
 { 7.20 , 7.37 , 7.55 , 7.73 , 7.92 , 8.11 , 8.31 , 8.51 , 8.72 , 8.94 , 9.16 , 9.39 , 9.63 , 9.87 , 10.12 , 10.37 , 10.64 }, 
 { 7.00 , 7.16 , 7.33 , 7.51 , 7.69 , 7.88 , 8.07 , 8.27 , 8.47 , 8.68 , 8.89 , 9.11 , 9.34 , 9.57 , 9.81 , 10.06 , 10.31 }, 
 { 6.79 , 6.95 , 7.12 , 7.28 , 7.46 , 7.64 , 7.82 , 8.01 , 8.21 , 8.41 , 8.61 , 8.82 , 9.04 , 9.27 , 9.50 , 9.74 , 9.98 }, 
 { 6.58 , 6.73 , 6.89 , 7.05 , 7.22 , 7.39 , 7.57 , 7.75 , 7.93 , 8.13 , 8.32 , 8.53 , 8.74 , 8.95 , 9.17 , 9.40 , 9.64 }, 
 { 6.37 , 6.51 , 6.66 , 6.82 , 6.97 , 7.14 , 7.31 , 7.48 , 7.66 , 7.84 , 8.03 , 8.22 , 8.42 , 8.63 , 8.84 , 9.06 , 9.28 }, 
 { 6.12 , 6.26 , 6.40 , 6.55 , 6.70 , 6.86 , 7.02 , 7.18 , 7.35 , 7.53 , 7.71 , 7.90 , 8.09 , 8.28 , 8.48 , 8.69 , 8.91 }, 
 { 5.92 , 6.05 , 6.19 , 6.33 , 6.47 , 6.62 , 6.77 , 6.93 , 7.09 , 7.25 , 7.42 , 7.60 , 7.78 , 7.97 , 8.16 , 8.35 , 8.56 }, 
 { 5.70 , 5.82 , 5.95 , 6.08 , 6.22 , 6.36 , 6.50 , 6.65 , 6.80 , 6.96 , 7.12 , 7.29 , 7.46 , 7.63 , 7.81 , 8.00 , 8.19 }, 
 { 5.48 , 5.59 , 5.71 , 5.84 , 5.96 , 6.10 , 6.23 , 6.37 , 6.51 , 6.66 , 6.81 , 6.97 , 7.13 , 7.30 , 7.47 , 7.64 , 7.82 }, 
 { 5.26 , 5.37 , 5.48 , 5.59 , 5.71 , 5.84 , 5.96 , 6.09 , 6.23 , 6.37 , 6.51 , 6.66 , 6.81 , 6.97 , 7.13 , 7.29 , 7.46 }, 
 { 5.04 , 5.14 , 5.25 , 5.35 , 5.47 , 5.58 , 5.70 , 5.82 , 5.95 , 6.08 , 6.21 , 6.35 , 6.49 , 6.64 , 6.79 , 6.94 , 7.10 }, 
 { 4.83 , 4.92 , 5.02 , 5.12 , 5.23 , 5.33 , 5.44 , 5.56 , 5.68 , 5.80 , 5.92 , 6.05 , 6.18 , 6.32 , 6.46 , 6.60 , 6.75 }, 
 { 4.62 , 4.71 , 4.80 , 4.89 , 4.99 , 5.09 , 5.19 , 5.30 , 5.41 , 5.52 , 5.64 , 5.76 , 5.88 , 6.01 , 6.14 , 6.27 , 6.41 }, 
 { 4.42 , 4.51 , 4.59 , 4.68 , 4.77 , 4.86 , 4.95 , 5.05 , 5.15 , 5.26 , 5.37 , 5.48 , 5.59 , 5.71 , 5.83 , 5.96 , 6.08 }, 
 { 4.23 , 4.31 , 4.39 , 4.47 , 4.55 , 4.64 , 4.73 , 4.82 , 4.91 , 5.01 , 5.11 , 5.21 , 5.31 , 5.42 , 5.54 , 5.65 , 5.77 }, 
 { 4.05 , 4.12 , 4.20 , 4.27 , 4.35 , 4.43 , 4.51 , 4.59 , 4.68 , 4.77 , 4.86 , 4.95 , 5.05 , 5.15 , 5.26 , 5.36 , 5.47 }, 
 { 3.89 , 3.95 , 4.02 , 4.08 , 4.15 , 4.23 , 4.30 , 4.38 , 4.46 , 4.54 , 4.62 , 4.71 , 4.80 , 4.89 , 4.99 , 5.09 , 5.19 }, 
 { 3.73 , 3.78 , 3.85 , 3.91 , 3.97 , 4.04 , 4.11 , 4.18 , 4.25 , 4.33 , 4.40 , 4.48 , 4.57 , 4.65 , 4.74 , 4.83 , 4.92 }, 
								 }	;

static float hummatric14[18][17] ={ 
 { 6.77 , 6.94 , 7.12 , 7.30 , 7.49 , 7.68 , 7.88 , 8.08 , 8.29 , 8.51 , 8.73 , 8.96 , 9.20 , 9.44 , 9.69 , 9.95 , 10.21 }, 
 { 6.57 , 6.73 , 6.90 , 7.08 , 7.26 , 7.45 , 7.64 , 7.84 , 8.04 , 8.25 , 8.46 , 8.68 , 8.91 , 9.14 , 9.38 , 9.63 , 9.89 }, 
 { 6.36 , 6.52 , 6.69 , 6.86 , 7.03 , 7.21 , 7.39 , 7.58 , 7.78 , 7.98 , 8.18 , 8.39 , 8.61 , 8.84 , 9.07 , 9.31 , 9.55 }, 
 { 6.15 , 6.30 , 6.46 , 6.62 , 6.79 , 6.96 , 7.14 , 7.32 , 7.50 , 7.70 , 7.89 , 8.10 , 8.31 , 8.52 , 8.74 , 8.97 , 9.21 }, 
 { 5.94 , 6.08 , 6.23 , 6.39 , 6.54 , 6.71 , 6.88 , 7.05 , 7.23 , 7.41 , 7.60 , 7.79 , 7.99 , 8.20 , 8.41 , 8.63 , 8.85 }, 
 { 5.70 , 5.84 , 5.98 , 6.13 , 6.28 , 6.43 , 6.59 , 6.76 , 6.93 , 7.11 , 7.29 , 7.47 , 7.66 , 7.86 , 8.06 , 8.27 , 8.48 }, 
 { 5.49 , 5.62 , 5.76 , 5.90 , 6.04 , 6.19 , 6.34 , 6.50 , 6.66 , 6.82 , 7.00 , 7.17 , 7.35 , 7.54 , 7.73 , 7.93 , 8.13 }, 
 { 5.27 , 5.39 , 5.52 , 5.65 , 5.79 , 5.93 , 6.07 , 6.22 , 6.37 , 6.53 , 6.69 , 6.86 , 7.03 , 7.20 , 7.38 , 7.57 , 7.76 }, 
 { 5.05 , 5.16 , 5.28 , 5.41 , 5.53 , 5.67 , 5.80 , 5.94 , 6.08 , 6.23 , 6.38 , 6.54 , 6.70 , 6.87 , 7.04 , 7.21 , 7.39 }, 
 { 4.83 , 4.94 , 5.05 , 5.16 , 5.28 , 5.41 , 5.53 , 5.66 , 5.80 , 5.94 , 6.08 , 6.23 , 6.38 , 6.54 , 6.70 , 6.86 , 7.03 }, 
 { 4.61 , 4.71 , 4.82 , 4.93 , 5.04 , 5.15 , 5.27 , 5.39 , 5.52 , 5.65 , 5.78 , 5.92 , 6.06 , 6.21 , 6.36 , 6.51 , 6.67 }, 
 { 4.40 , 4.49 , 4.59 , 4.69 , 4.80 , 4.90 , 5.01 , 5.13 , 5.25 , 5.37 , 5.49 , 5.62 , 5.75 , 5.89 , 6.03 , 6.17 , 6.32 }, 
 { 4.19 , 4.28 , 4.37 , 4.47 , 4.56 , 4.66 , 4.76 , 4.87 , 4.98 , 5.09 , 5.21 , 5.33 , 5.45 , 5.58 , 5.71 , 5.84 , 5.98 }, 
 { 3.99 , 4.08 , 4.16 , 4.25 , 4.34 , 4.43 , 4.53 , 4.62 , 4.72 , 4.83 , 4.94 , 5.05 , 5.16 , 5.28 , 5.40 , 5.53 , 5.65 }, 
 { 3.80 , 3.88 , 3.96 , 4.04 , 4.12 , 4.21 , 4.30 , 4.39 , 4.48 , 4.58 , 4.68 , 4.78 , 4.88 , 4.99 , 5.11 , 5.22 , 5.34 }, 
 { 3.63 , 3.69 , 3.77 , 3.84 , 3.92 , 4.00 , 4.08 , 4.16 , 4.25 , 4.34 , 4.43 , 4.52 , 4.62 , 4.72 , 4.83 , 4.93 , 5.04 }, 
 { 3.46 , 3.52 , 3.59 , 3.65 , 3.72 , 3.80 , 3.87 , 3.95 , 4.03 , 4.11 , 4.19 , 4.28 , 4.37 , 4.46 , 4.56 , 4.66 , 4.76 }, 
 { 3.30 , 3.35 , 3.42 , 3.48 , 3.54 , 3.61 , 3.68 , 3.75 , 3.82 , 3.90 , 3.97 , 4.05 , 4.14 , 4.22 , 4.31 , 4.40 , 4.49 }, 
								 }	;



static float hummatric11[18][17] ={  
 { 6.36 , 6.53 , 6.71 , 6.89 , 7.08 , 7.27 , 7.47 , 7.68 , 7.89 , 8.10 , 8.33 , 8.56 , 8.79 , 9.03 , 9.28 , 9.54 , 9.80 }, 
 { 6.16 , 6.33 , 6.50 , 6.67 , 6.86 , 7.04 , 7.23 , 7.43 , 7.63 , 7.84 , 8.06 , 8.28 , 8.50 , 8.74 , 8.98 , 9.23 , 9.48 }, 
 { 5.96 , 6.12 , 6.28 , 6.45 , 6.62 , 6.80 , 6.99 , 7.18 , 7.37 , 7.57 , 7.78 , 7.99 , 8.21 , 8.43 , 8.66 , 8.90 , 9.14 }, 
 { 5.75 , 5.90 , 6.06 , 6.22 , 6.38 , 6.56 , 6.73 , 6.91 , 7.10 , 7.29 , 7.49 , 7.69 , 7.90 , 8.12 , 8.34 , 8.57 , 8.80 }, 
 { 5.53 , 5.68 , 5.83 , 5.98 , 6.14 , 6.30 , 6.47 , 6.64 , 6.82 , 7.01 , 7.19 , 7.39 , 7.59 , 7.79 , 8.01 , 8.22 , 8.45 }, 
 { 5.30 , 5.44 , 5.58 , 5.73 , 5.88 , 6.03 , 6.19 , 6.36 , 6.53 , 6.71 , 6.89 , 7.07 , 7.26 , 7.46 , 7.66 , 7.87 , 8.08 }, 
 { 5.09 , 5.22 , 5.35 , 5.49 , 5.64 , 5.78 , 5.94 , 6.09 , 6.25 , 6.42 , 6.59 , 6.77 , 6.95 , 7.13 , 7.32 , 7.52 , 7.72 }, 
 { 4.86 , 4.99 , 5.12 , 5.25 , 5.38 , 5.52 , 5.67 , 5.81 , 5.97 , 6.12 , 6.28 , 6.45 , 6.62 , 6.80 , 6.98 , 7.16 , 7.36 }, 
 { 4.64 , 4.76 , 4.88 , 5.00 , 5.13 , 5.26 , 5.40 , 5.54 , 5.68 , 5.83 , 5.98 , 6.13 , 6.30 , 6.46 , 6.63 , 6.81 , 6.99 }, 
 { 4.42 , 4.53 , 4.64 , 4.76 , 4.88 , 5.00 , 5.13 , 5.26 , 5.39 , 5.53 , 5.68 , 5.82 , 5.97 , 6.13 , 6.29 , 6.46 , 6.62 }, 
 { 4.20 , 4.31 , 4.41 , 4.52 , 4.63 , 4.75 , 4.87 , 4.99 , 5.11 , 5.24 , 5.38 , 5.52 , 5.66 , 5.80 , 5.95 , 6.11 , 6.27 }, 
 { 3.99 , 4.09 , 4.18 , 4.29 , 4.39 , 4.50 , 4.61 , 4.72 , 4.84 , 4.96 , 5.09 , 5.21 , 5.35 , 5.48 , 5.62 , 5.77 , 5.92 }, 
 { 3.79 , 3.87 , 3.97 , 4.06 , 4.16 , 4.26 , 4.36 , 4.47 , 4.57 , 4.69 , 4.80 , 4.92 , 5.05 , 5.17 , 5.30 , 5.44 , 5.58 }, 
 { 3.59 , 3.67 , 3.75 , 3.84 , 3.93 , 4.02 , 4.12 , 4.22 , 4.32 , 4.42 , 4.53 , 4.64 , 4.76 , 4.87 , 5.00 , 5.12 , 5.25 }, 
 { 3.40 , 3.47 , 3.55 , 3.63 , 3.72 , 3.80 , 3.89 , 3.98 , 4.07 , 4.17 , 4.27 , 4.37 , 4.48 , 4.59 , 4.70 , 4.82 , 4.93 }, 
 { 3.22 , 3.29 , 3.36 , 3.44 , 3.51 , 3.59 , 3.67 , 3.76 , 3.84 , 3.93 , 4.02 , 4.12 , 4.22 , 4.32 , 4.42 , 4.53 , 4.64 }, 
 { 3.05 , 3.11 , 3.18 , 3.25 , 3.32 , 3.39 , 3.47 , 3.54 , 3.62 , 3.70 , 3.79 , 3.88 , 3.97 , 4.06 , 4.15 , 4.25 , 4.35 }, 
 { 2.89 , 2.95 , 3.01 , 3.07 , 3.14 , 3.20 , 3.27 , 3.34 , 3.42 , 3.49 , 3.57 , 3.65 , 3.73 , 3.82 , 3.90 , 4.00 , 4.09 }, 
								 }	;

//static float hummatric14[12][7] ={ {6.77, 7.12, 7.49, 7.88, 8.29, 8.73, 9.20   },
//                                   {6.57, 6.90, 7.26, 7.64, 8.04, 8.46, 8.91   },
//                                   {6.36, 6.69, 7.03, 7.39, 7.78, 8.18, 8.61   },
//								   {6.15, 6.46, 6.79, 7.14, 7.50, 7.89, 8.31   },
//								   {5.94, 6.23, 6.54, 6.88, 7.23, 7.60, 7.99    },
//								   {5.72, 6.00, 6.29, 6.61, 6.94, 7.30, 7.67    },
//								   {5.49, 5.76, 6.04, 6.34, 6.66, 7.00, 7.35   },
//								   {5.27, 5.52, 5.79, 6.07, 6.37, 6.69, 7.03   },
//								   {5.05, 5.28, 5.53, 5.80, 6.08, 6.38, 6.70   },
//								   {4.83, 5.05, 5.28, 5.53, 5.80, 6.08, 6.38    },
//								   {4.19, 4.37, 4.56, 4.76, 4.98, 5.21, 5.45  },
//								   {3.80, 3.96, 4.12, 4.30, 4.48, 4.68, 4.88   },
//								 }	;





static float   hummatric[18][17]={0};
static float   Centers[NEURALNUM][8]   ={0}	 ;
static float   Betas[NEURALNUM] ={0};
static float   Thetas[NEURALNUM+1] ={0};
 
                            
float  Lookup_table(float Daq[],float setpoint[],float arout[8],u8 panelControl);

u8     flowrate_adj( float flowratestep,float arin[],float arout[],float analogIn[]);
u8     highlevel_alarm(float Daq,u8 panelControl,float arin[12] );
u8     lowlevel_sv_alarm(float Daq,u8 panelControl,float arin[12]);
u8     lowlevel_pump_alarm(float Daq,u8 panelControl,float arin[12]);
void   circulation_alarm(float arout[],u8 panelControl,float arin[12]);
//u8     arrary_compare(float Daq_temp[],float Daq[]);
u8     solutiontransfer(float Daq[],u8 panelControl,float arout[12] );
//float  *plastdata(float *pData_temp,float *pData);
void   coolingsource_alarm(void);	
u8     dehStart(float Setpoint[3],u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8],u8 dehflag);
u8     dehStop(float arin[12],float arout[8],u8 dout[8]);
void   deInit(float arr[8]);
void   deClever(float aout[8],u8 dout[8]);
void   deDefault(void);
void    ctrlalgorthim (float Daq[],float setpoint[],float arout[8],float arin[12],float outlethumN[12],float outletTemN[12] );
//float    checktendency(float outlethumN[12],u8 n,float humsstep,float setpoint[3]);
float  RH2HR(float temp, float relativehum);
u8     Deh_algorithm (float Setpoint[3], u8 digitalIn[8],u8 digitalOut[8],float analogInold[16],float analogIn[16],float rangeIn[12],float analogOut[8],float rangeOut[8], u8 panelControl,float outlethumN[12],float outletTemN[12]) ;
float     SolInletPID(float analogIn[16],float aimed_solultiontemp,float arout[],u8 panelControl);
void   pumplimcheck(u8 pumpflag,float step);
u8     flowrate_set(float flowratestep,float arout[8],float analogIn[16] ) ;
//u8     lesacalogrithm(float Setpoint[],float analogIn[16],float rangeIn[12],float analogOut[8],float rangeOut[8], u8 panelControl);
u8     cs_set(float csvacstep,float arout[8],float analogIn[16] )	;
float density(float temperature, float concen );
float opentimecnt(float analogIn[16],float tempTa,float concenw,float concens,float caim);
void valveopen(float t);
float caimdetermin(float Setpoint[3], float conNow,float SolInTNow);
float softsensing(float analogIn[16]);
void concenalgorithm(float Setpoint[],float analogIn[16],float rangeIn[12],float analogOut[8],float rangeOut[8], u8 panelControl) ;

extern u8 algorithmstart;
extern u8 flowratecntH;
extern u8 flowratecntL;				  
extern float concentration ;
static float templocker=0;
static float  aimed_solultiontemp=0;
#endif
