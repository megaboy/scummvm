/* ScummVM - Scumm Interpreter
 * Copyright (C) 2003 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$ 
 *
 */

#ifndef SKY37COMP_H
#define SKY37COMP_H




namespace Sky {

namespace SkyCompact {

uint16 sc37_mouse_list[] = {
	ID_SC37_SENSOR,
	ID_SC37_DOOR,
	ID_SC37_GRILL,
	ID_SC37_FLIMSY_BOX,
	ID_SC37_LID,
	ID_SC37_BIG_BOX,
	ID_SC37_WINE_RACK,
	ID_SC37_FLOOR,
	0XFFFF,
	ID_TEXT_MOUSE
};

uint16 sc37_chip_list[] = {
	IT_SC37_LAYER_0+DISK_13,
	IT_SC37_LAYER_1+DISK_13,
	IT_SC37_LAYER_2+DISK_13,
	IT_SC37_GRID_1+DISK_13,
	IT_SC37_GRID_2+DISK_13,
	IT_SC37_CRBARBOX+DISK_13+0X8000,
	IT_SC37_GETLID+DISK_13,
	IT_SC37_USELID+DISK_13+0X8000,
	IT_SC37_STEPUP+DISK_13,
	IT_SC37_FOOTDROP+DISK_13,
	IT_SC37_STEPDOWN+DISK_13,
	IT_SC37_USEBAR+DISK_13+0X8000,
	IT_SC37_USESEC+DISK_13+0X8000,
	IT_SC37_CLIMBOUT+DISK_13+0X8000,
	IT_SC37_THUMBSUP+DISK_13,
	IT_SC37_BOXLID+DISK_13,
	IT_SC37_LIDUP+DISK_13,
	IT_SC37_LIDUSED+DISK_13,
	IT_SC37_LOOSEBIT+DISK_13,
	IT_SC37_GRILL+DISK_13,
	IT_SC37_GRILLOPEN+DISK_13,
	IT_SC37_DOOR+DISK_13,
	0
};

uint16 sc37_grillopen[] = {
	142*64,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	0,
	307,
	192,
	1,
	307,
	192,
	2,
	307,
	192,
	3,
	307,
	192,
	4,
	0
};

uint16 sc37_floor_table[] = {
	ID_SC37_FLOOR,
	RET_OK,
	ID_SC37_DOOR,
	GT_SC37_DOOR,
	0,
	SC37_DOOR_WALK_ON,
	ID_SC37_SENSOR,
	GT_SC37_SENSOR,
	ID_SC37_GRILL,
	GT_SC37_GRILL,
	ID_SC37_FLIMSY_BOX,
	GT_SC37_FLIMSY_BOX,
	ID_SC37_BIG_BOX,
	GT_SC37_BIG_BOX,
	ID_SC37_LID,
	GT_SC37_LID,
	ID_SC37_WINE_RACK,
	GT_SC37_WINE_RACK,
	65535
};

uint16 sc37_stepdown[] = {
	131*64,
	309,
	194,
	0,
	304,
	200,
	1,
	304,
	210,
	2,
	304,
	217,
	3,
	304,
	218,
	4,
	304,
	219,
	5,
	304,
	221,
	6,
	304,
	224,
	7,
	303,
	224,
	8,
	304,
	224,
	9,
	307,
	222,
	10,
	309,
	218,
	0,
	0
};

Compact sc37_big_box = {
	0,	// logic
	ST_MOUSE,	// status
	0,	// sync
	37,	// screen
	0,	// place
	0,	// getToTable
	219,	// xcood
	231,	// ycood
	0,	// frame
	16659,	// cursorText
	STD_ON,	// mouseOn
	STD_OFF,	// mouseOff
	ADVISOR_188,	// mouseClick
	0,	// mouseRel_x
	0,	// mouseRel_y
	269-219,	// mouseSize_x
	278-231,	// mouseSize_y
	SC37_BIG_BOX_ACTION,	// actionScript
	0,
	0,
	0,
	0,
	0,
	{ 0, 0, 0 },
	0,
	0,
	0,
	0,
	0
};

uint16 sc37_footdrop[] = {
	130*64,
	309,
	194,
	0,
	302,
	197,
	1,
	299,
	203,
	2,
	299,
	201,
	3,
	309,
	194,
	0,
	0
};

uint16 sc37_putlid[] = {
	109*64,
	260,
	218,
	7,
	254,
	219,
	6,
	247,
	223,
	5,
	247,
	223,
	4,
	256,
	222,
	3,
	263,
	221,
	2,
	267,
	218,
	1,
	268,
	218,
	0,
	0
};

Compact sc37_sensor = {
	0,	// logic
	ST_MOUSE,	// status
	0,	// sync
	37,	// screen
	0,	// place
	0,	// getToTable
	185,	// xcood
	238,	// ycood
	0,	// frame
	16651,	// cursorText
	STD_ON,	// mouseOn
	STD_OFF,	// mouseOff
	ADVISOR_188,	// mouseClick
	0,	// mouseRel_x
	0,	// mouseRel_y
	190-185,	// mouseSize_x
	248-238,	// mouseSize_y
	SC37_SENSOR_ACTION,	// actionScript
	0,
	0,
	0,
	0,
	0,
	{ 0, 0, 0 },
	0,
	0,
	0,
	0,
	0
};

uint16 sc37_lidused[] = {
	139*64,
	258,
	218,
	0,
	251,
	218,
	1,
	256,
	218,
	2,
	266,
	218,
	3,
	279,
	217,
	4,
	286,
	218,
	5,
	290,
	218,
	6,
	293,
	218,
	7,
	296,
	219,
	7,
	300,
	219,
	7,
	304,
	218,
	7,
	308,
	219,
	7,
	311,
	219,
	7,
	315,
	219,
	7,
	319,
	218,
	7,
	318,
	217,
	4,
	318,
	217,
	4,
	321,
	218,
	8,
	312,
	217,
	9,
	305,
	217,
	10,
	305,
	223,
	11,
	305,
	235,
	12,
	305,
	240,
	13,
	305,
	240,
	14,
	305,
	240,
	15,
	305,
	240,
	16,
	0
};

uint16 sc37_getlid[] = {
	109*64,
	268,
	218,
	0,
	267,
	218,
	1,
	263,
	221,
	2,
	256,
	222,
	3,
	247,
	223,
	4,
	247,
	223,
	5,
	254,
	219,
	6,
	260,
	218,
	7,
	0
};

uint16 sc37_flimsy_box_table[] = {
	ID_SC37_FLOOR,
	STEP_OFF_BOX,
	ID_SC37_DOOR,
	STEP_OFF_BOX,
	ID_SC37_SENSOR,
	STEP_OFF_BOX,
	ID_SC37_GRILL,
	GT_SC37_GRILL,
	ID_SC37_FLIMSY_BOX,
	RET_OK,
	ID_SC37_BIG_BOX,
	STEP_OFF_BOX,
	ID_SC37_WINE_RACK,
	STEP_OFF_BOX,
	65535
};

uint16 sc37_thumbsup[] = {
	136*64,
	204,
	226,
	0,
	202,
	227,
	1,
	202,
	227,
	2,
	201,
	227,
	3,
	195,
	229,
	4,
	187,
	229,
	5,
	187,
	229,
	5,
	187,
	229,
	5,
	195,
	229,
	4,
	201,
	227,
	6,
	202,
	227,
	2,
	202,
	227,
	1,
	204,
	226,
	0,
	0
};

Compact sc37_wine_rack = {
	0,	// logic
	ST_MOUSE,	// status
	0,	// sync
	37,	// screen
	0,	// place
	0,	// getToTable
	351,	// xcood
	208,	// ycood
	0,	// frame
	17379,	// cursorText
	STD_ON,	// mouseOn
	STD_OFF,	// mouseOff
	ADVISOR_188,	// mouseClick
	0,	// mouseRel_x
	0,	// mouseRel_y
	402-351,	// mouseSize_x
	280-208,	// mouseSize_y
	SC37_WINE_RACK_ACTION,	// actionScript
	0,
	0,
	0,
	0,
	0,
	{ 0, 0, 0 },
	0,
	0,
	0,
	0,
	0
};

uint16 sc37_fast_list[] = {
	12+DISK_13,
	51+DISK_13,
	52+DISK_13,
	53+DISK_13,
	54+DISK_13,
	135+DISK_13,
	0
};

uint16 sc37_holding_lid_table[] = {
	ID_SC37_FLOOR,
	PUT_LID_BACK,
	ID_SC37_DOOR,
	PUT_LID_BACK,
	ID_SC37_SENSOR,
	PUT_LID_BACK,
	ID_SC37_GRILL,
	PUT_LID_BACK,
	ID_SC37_FLIMSY_BOX,
	USE_LID_ON_FLIMSY_BOX,
	ID_SC37_BIG_BOX,
	PUT_LID_BACK,
	ID_SC37_WINE_RACK,
	PUT_LID_BACK,
	65535
};

Compact sc37_holding_lid = {
	0,	// logic
	0,	// status
	0,	// sync
	37,	// screen
	0,	// place
	sc37_holding_lid_table,	// getToTable
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	{ 0, 0, 0 },
	0,
	0,
	0,
	0,
	0
};

uint16 sc37_lidup[] = {
	138*64,
	231,
	234,
	0,
	250,
	222,
	1,
	256,
	218,
	2,
	0
};

uint16 sc37_usesec[] = {
	133*64,
	304,
	192,
	0,
	304,
	192,
	1,
	304,
	192,
	2,
	304,
	192,
	3,
	304,
	192,
	4,
	304,
	192,
	5,
	304,
	192,
	5,
	304,
	192,
	6,
	304,
	192,
	7,
	304,
	192,
	8,
	304,
	192,
	9,
	304,
	192,
	10,
	304,
	192,
	11,
	304,
	192,
	12,
	304,
	192,
	13,
	304,
	192,
	14,
	304,
	192,
	15,
	304,
	192,
	15,
	304,
	192,
	16,
	304,
	192,
	17,
	304,
	192,
	17,
	304,
	192,
	18,
	304,
	192,
	19,
	304,
	192,
	19,
	304,
	192,
	20,
	304,
	192,
	21,
	304,
	192,
	21,
	304,
	192,
	22,
	304,
	192,
	23,
	304,
	192,
	23,
	304,
	192,
	24,
	304,
	192,
	25,
	304,
	192,
	25,
	304,
	192,
	26,
	304,
	192,
	27,
	304,
	192,
	28,
	304,
	192,
	29,
	304,
	192,
	30,
	304,
	192,
	30,
	304,
	192,
	31,
	304,
	192,
	32,
	304,
	192,
	33,
	304,
	192,
	34,
	304,
	192,
	35,
	304,
	192,
	36,
	304,
	192,
	37,
	304,
	192,
	38,
	304,
	192,
	39,
	304,
	192,
	40,
	304,
	192,
	41,
	304,
	192,
	42,
	304,
	192,
	0,
	0
};

uint16 sc37_stepup[] = {
	129*64,
	309,
	218,
	0,
	305,
	223,
	1,
	303,
	224,
	2,
	303,
	224,
	3,
	303,
	224,
	4,
	303,
	222,
	5,
	303,
	220,
	6,
	301,
	218,
	7,
	302,
	213,
	8,
	302,
	212,
	9,
	302,
	208,
	10,
	306,
	200,
	11,
	309,
	194,
	12,
	309,
	194,
	12,
	0
};

Compact sc37_lid = {
	L_SCRIPT,	// logic
	ST_LOGIC+ST_BACKGROUND+ST_RECREATE,	// status
	0,	// sync
	37,	// screen
	0,	// place
	0,	// getToTable
	230,	// xcood
	234,	// ycood
	137*64,	// frame
	201,	// cursorText
	STD_ON,	// mouseOn
	STD_OFF,	// mouseOff
	ADVISOR_188,	// mouseClick
	1,	// mouseRel_x
	(int16) 65535,	// mouseRel_y
	267-231,	// mouseSize_x
	244-233,	// mouseSize_y
	SC37_LID_ACTION,	// actionScript
	0,	// upFlag
	0,	// downFlag
	0,	// getToFlag
	0,	// flag
	0,	// mood
	{ 0, 0, 0 },
	0,	// offset
	C_BASE_MODE,	// mode
	SC37_LID_LOGIC,	// baseSub
	0,	// baseSub_off
	0
};

uint16 sc37_palette[] = {
	0,
	768,
	514,
	770,
	1027,
	771,
	1029,
	770,
	773,
	1029,
	1028,
	1285,
	1541,
	1795,
	773,
	1286,
	1285,
	1542,
	1288,
	1541,
	1031,
	1543,
	2054,
	1031,
	2055,
	2565,
	1030,
	2055,
	2311,
	1543,
	2058,
	2053,
	1545,
	1803,
	2566,
	1800,
	2060,
	2053,
	2058,
	2060,
	2567,
	1546,
	2570,
	3080,
	1546,
	2318,
	3078,
	2058,
	2827,
	2567,
	2316,
	3084,
	3337,
	1803,
	2574,
	3080,
	1549,
	3339,
	4104,
	1802,
	3341,
	3592,
	2316,
	2831,
	3590,
	2571,
	3087,
	3080,
	2829,
	3089,
	4102,
	2315,
	3089,
	4104,
	1805,
	3342,
	3339,
	2574,
	3344,
	4618,
	1805,
	3599,
	3593,
	2063,
	3346,
	4361,
	2062,
	3600,
	3340,
	3343,
	3854,
	4619,
	2829,
	3856,
	5130,
	2573,
	4111,
	4876,
	2062,
	4113,
	3849,
	2577,
	4113,
	5387,
	2318,
	3858,
	4618,
	3087,
	4115,
	5385,
	2064,
	4368,
	5133,
	2575,
	4625,
	4873,
	2832,
	3860,
	4876,
	3344,
	4370,
	4108,
	2579,
	4372,
	5386,
	2832,
	4117,
	4621,
	3601,
	4372,
	4876,
	2834,
	4372,
	5646,
	2577,
	4119,
	4619,
	3091,
	4881,
	4878,
	3346,
	4376,
	4874,
	3858,
	4629,
	4879,
	3604,
	4631,
	5131,
	4116,
	5141,
	6414,
	2834,
	4886,
	5136,
	4374,
	5398,
	6671,
	3093,
	5655,
	6930,
	3350,
	5913,
	6161,
	4887,
	5661,
	6413,
	5144,
	5914,
	6931,
	5144,
	6683,
	7956,
	3865,
	8227,
	7183,
	6945,
	8486,
	9494,
	6438,
	10790,
	11294,
	6955,
	11309,
	12064,
	6702,
	11823,
	12834,
	8498,
	12593,
	13863,
	10293,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	0,
	14336,
	13364,
	11569,
	9261,
	8481,
	6687,
	6681,
	4626,
	2578,
	1803,
	770,
	519,
	13571,
	9517,
	9778,
	11805,
	5151,
	5926,
	8205,
	1808,
	2586,
	11267,
	2056,
	8210,
	7441,
	6954,
	9494,
	4119,
	3866,
	4864,
	13316,
	13364,
	11563,
	8751,
	9506,
	10024,
	8242,
	10527,
	6174,
	5927,
	7698,
	3600,
	2325,
	2308,
	11573,
	12837,
	7462,
	7982,
	9748,
	3351,
	4128,
	6663,
	778,
	9533,
	13100,
	9244,
	5162,
	8476,
	5390,
	2072,
	3855,
	2308,
	2865,
	9995,
	1285,
	285,
	4865,
	0,
	11573,
	12837,
	7462,
	0,
	16128,
	0,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	13887,
	13878,
	12077,
	8241,
	10527,
	5917,
	5925,
	7698,
	2865,
	9995,
	1285,
	285,
	16129,
	16191
};

Compact sc37_floor = {
	0,	// logic
	ST_MOUSE,	// status
	0,	// sync
	37,	// screen
	0,	// place
	sc37_floor_table,	// getToTable
	192,	// xcood
	256,	// ycood
	0,	// frame
	0,	// cursorText
	0,	// mouseOn
	0,	// mouseOff
	ADVISOR_188,	// mouseClick
	0,	// mouseRel_x
	0,	// mouseRel_y
	399-192,	// mouseSize_x
	319-256,	// mouseSize_y
	FLOOR_ACTION,	// actionScript
	0,
	0,
	0,
	0,
	0,
	{ 0, 0, 0 },
	0,
	0,
	0,
	0,
	0
};

uint16 sc37_climbout[] = {
	134*64,
	309,
	194,
	0,
	307,
	194,
	1,
	303,
	194,
	2,
	308,
	194,
	3,
	308,
	194,
	3,
	308,
	195,
	4,
	308,
	196,
	5,
	309,
	195,
	6,
	309,
	196,
	7,
	309,
	194,
	8,
	308,
	193,
	9,
	309,
	193,
	10,
	309,
	192,
	11,
	308,
	192,
	12,
	308,
	194,
	13,
	309,
	193,
	14,
	309,
	193,
	15,
	309,
	192,
	16,
	0
};

Compact sc37_grill = {
	L_SCRIPT,	// logic
	ST_MOUSE+ST_LOGIC+ST_BACKGROUND+ST_RECREATE,	// status
	0,	// sync
	37,	// screen
	0,	// place
	0,	// getToTable
	307,	// xcood
	192,	// ycood
	141*64,	// frame
	16661,	// cursorText
	STD_ON,	// mouseOn
	STD_OFF,	// mouseOff
	ADVISOR_188,	// mouseClick
	(int16) 65535,	// mouseRel_x
	(int16) 65535,	// mouseRel_y
	335-306,	// mouseSize_x
	208-191,	// mouseSize_y
	SC37_GRILL_ACTION,	// actionScript
	0,	// upFlag
	0,	// downFlag
	0,	// getToFlag
	0,	// flag
	0,	// mood
	{ 0, 0, 0 },
	0,	// offset
	C_BASE_MODE,	// mode
	SC37_GRILL_LOGIC,	// baseSub
	0,	// baseSub_off
	0
};

uint16 sc37_uselid[] = {
	110*64,
	262,
	218,
	0,
	254,
	218,
	1,
	255,
	218,
	2,
	263,
	218,
	3,
	272,
	217,
	4,
	273,
	217,
	5,
	273,
	217,
	6,
	274,
	217,
	7,
	277,
	218,
	8,
	286,
	218,
	9,
	292,
	217,
	10,
	292,
	218,
	11,
	293,
	218,
	12,
	298,
	218,
	13,
	306,
	217,
	14,
	310,
	217,
	15,
	310,
	217,
	16,
	310,
	217,
	17,
	309,
	217,
	18,
	304,
	217,
	19,
	304,
	219,
	20,
	304,
	219,
	21,
	304,
	221,
	22,
	304,
	219,
	23,
	309,
	218,
	24,
	0
};

uint16 reset_36_37[] = {
	C_SCREEN,
	37,
	C_PLACE,
	ID_SC37_FLOOR,
	C_XCOOD,
	176,
	C_YCOOD,
	272,
	C_FRAME,
	46+12*64,
	65535
};

uint16 sc37_doorshut[] = {
	143*64,
	196,
	221,
	6,
	196,
	221,
	5,
	196,
	221,
	4,
	196,
	221,
	3,
	196,
	221,
	2,
	196,
	221,
	1,
	196,
	221,
	0,
	0
};

uint32 *sc37_walk_grid = (uint32*)sc37_fast_list;

Compact sc37_door = {
	L_SCRIPT,	// logic
	ST_MOUSE+ST_LOGIC+ST_RECREATE,	// status
	0,	// sync
	37,	// screen
	0,	// place
	0,	// getToTable
	196,	// xcood
	221,	// ycood
	143*64,	// frame
	181,	// cursorText
	STD_ON,	// mouseOn
	STD_OFF,	// mouseOff
	ADVISOR_188,	// mouseClick
	(int16) 65532,	// mouseRel_x
	(int16) 65531,	// mouseRel_y
	207-192,	// mouseSize_x
	279-216,	// mouseSize_y
	SC37_DOOR_ACTION,	// actionScript
	0,	// upFlag
	0,	// downFlag
	0,	// getToFlag
	0,	// flag
	0,	// mood
	{ 0, 0, 0 },
	0,	// offset
	C_BASE_MODE,	// mode
	SC37_DOOR_LOGIC,	// baseSub
	0,	// baseSub_off
	0
};

uint16 sc37_usebar[] = {
	132*64,
	309,
	194,
	0,
	308,
	194,
	1,
	306,
	195,
	2,
	306,
	195,
	3,
	306,
	195,
	4,
	306,
	195,
	4,
	306,
	195,
	5,
	306,
	195,
	6,
	306,
	195,
	6,
	306,
	195,
	7,
	306,
	195,
	7,
	307,
	195,
	8,
	309,
	194,
	9,
	309,
	194,
	10,
	308,
	194,
	11,
	307,
	194,
	12,
	303,
	194,
	13,
	306,
	194,
	14,
	306,
	194,
	15,
	304,
	195,
	16,
	304,
	195,
	16,
	309,
	195,
	17,
	310,
	195,
	18,
	311,
	195,
	19,
	312,
	195,
	20,
	312,
	195,
	20,
	312,
	195,
	21,
	312,
	195,
	22,
	312,
	195,
	23,
	312,
	195,
	24,
	312,
	193,
	25,
	312,
	195,
	26,
	312,
	195,
	27,
	312,
	193,
	28,
	312,
	195,
	29,
	312,
	195,
	30,
	312,
	194,
	31,
	312,
	195,
	32,
	312,
	195,
	32,
	312,
	195,
	33,
	306,
	195,
	34,
	306,
	195,
	34,
	305,
	195,
	35,
	305,
	195,
	36,
	305,
	195,
	37,
	305,
	195,
	38,
	305,
	195,
	39,
	305,
	195,
	40,
	306,
	194,
	41,
	309,
	194,
	0,
	0
};

Compact sc37_flimsy_box = {
	0,	// logic
	ST_MOUSE+ST_BACKGROUND+ST_RECREATE,	// status
	0,	// sync
	37,	// screen
	0,	// place
	sc37_flimsy_box_table,	// getToTable
	318,	// xcood
	245,	// ycood
	140*64,	// frame
	16660,	// cursorText
	STD_ON,	// mouseOn
	STD_OFF,	// mouseOff
	ADVISOR_188,	// mouseClick
	(int16) 65518,	// mouseRel_x
	(int16) 65529,	// mouseRel_y
	333-300,	// mouseSize_x
	264-238,	// mouseSize_y
	SC37_FLIMSY_BOX_ACTION,	// actionScript
	0,
	0,
	0,
	0,
	0,
	{ 0, 0, 0 },
	0,
	0,
	0,
	0,
	0
};

uint16 sc37_dooropen[] = {
	143*64,
	196,
	221,
	0,
	196,
	221,
	1,
	196,
	221,
	2,
	196,
	221,
	3,
	196,
	221,
	4,
	196,
	221,
	5,
	196,
	221,
	6,
	0
};

uint16 sc37_liddown[] = {
	138*64,
	256,
	218,
	2,
	250,
	222,
	1,
	231,
	234,
	0,
	0
};

uint16 sc37_logic_list[] = {
	ID_FOSTER,
	ID_SC37_FLIMSY_BOX,
	ID_SC37_LID,
	ID_SC37_GRILL,
	ID_SC37_DOOR,
	0XFFFF,
	ID_STD_MENU_LOGIC
};

uint16 sc37_crbarbox[] = {
	108*64,
	264,
	216,
	0,
	264,
	216,
	1,
	264,
	216,
	2,
	264,
	216,
	3,
	264,
	216,
	4,
	264,
	216,
	5,
	264,
	216,
	6,
	264,
	216,
	7,
	264,
	216,
	8,
	264,
	216,
	9,
	264,
	216,
	10,
	264,
	216,
	11,
	264,
	216,
	12,
	264,
	216,
	13,
	264,
	216,
	14,
	264,
	216,
	15,
	264,
	216,
	14,
	264,
	216,
	16,
	264,
	216,
	16,
	264,
	216,
	17,
	264,
	216,
	18,
	264,
	216,
	19,
	264,
	216,
	20,
	264,
	216,
	21,
	264,
	216,
	22,
	264,
	216,
	23,
	264,
	216,
	24,
	264,
	216,
	25,
	264,
	216,
	26,
	0
};

} // namespace SkyCompact

} // namespace Sky

#endif
