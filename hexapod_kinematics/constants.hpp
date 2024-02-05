#pragma once

#include <stdint.h>
#include <string>

const std::string LEG_POINT_TYPES_LIST[] = {
	"bodyContactPoint",
	"coxiaPoint",
	"femurPoint",
	"footTipPoint",
};

enum POSITION_NAME_TO_ID_MAP {
	rightMiddle,
	rightFront,
	leftFront,
	leftMiddle,
	leftBack,
	rightBack
};

const std::string POSITION_NAMES_LIST[] = {
	"rightMiddle",
	"rightFront",
	"leftFront",
	"leftMiddle",
	"leftBack",
	"rightBack"
};

const std::string POSITION_NAMES_LIST[] = {
	"alpha", 
	"beta", 
	"gamma"    
};

enum POSITION_NAME_TO_ID_MAP {
	alpha = 90,
	beta = 180,
	gamma = 180
};

/*

	hexapodYaxis
			^
			|
			|
			*-----> hexapodXaxis
		/ (cog)
		/
hexapodZaxis

Relative x-axis, for each attached linkage

(+135)  x2          x1 (+45)
					\   head  /
					*---*---*
					/    |    \
				/     |     \
(+180)  /      |      \
	x3 --*------cog------*-- x0 (+0)
				\      |      /
				\     |     /
					\    |    /
					*---*---*
					/         \
				x4           x5
		(+225)        (+315)
*/
enum POSITION_NAME_TO_AXIS_ANGLE_MAP {
	rightMiddle = 0,
	rightFront = 45,
	leftFront = 135,
	leftMiddle = 180,
	leftBack = 225,
	rightBack = 315
};

const uint8_t NUMBER_OF_LEGS = 6;
