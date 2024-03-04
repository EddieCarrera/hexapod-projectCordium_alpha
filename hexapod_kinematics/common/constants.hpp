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

enum MAX_ANGLES {
	alpha_maxAngle = 90,
	beta_maxAngle = 180,
	gamma_maxAngle = 180
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
uint16_t POSITION_NAME_TO_AXIS_ANGLE_MAP[] {
	0, 	// rightMiddle
	45, 	// rightFront
	135, 	// leftFront
	180,	// leftMiddle
	225,		// leftBack
	315		// rightBack
};

const uint8_t NUMBER_OF_LEGS = 6;
