#pragma once
#include "test_common.hpp"

const static twoVectorIn_floatOut_t angleBetween_cases[3] = {
  {Vector(-127.3, 230.93, 0), Vector(-110.44, 239.45, 0 ), 4.1040798537345005}, 
  {Vector(-0.84, -0.55, 0.03), Vector(0.95, 0.3, 0.03), 163.94}, 
  {Vector(129.79, 0, -144.49), Vector(1, 0, 0), 48.068032085640155}
};

const static threeFloatIn_floatOut_t angleOppositeOfLastSide_case[2] = {
  {113.2947, 111, 119, 64.075933},
  {210.9919, 111, 121, 25.725479306694762}
};

const static threeVectorIn_vectorOut_t getNormalofThreePoints_case[2] = {
  {Vector(309.96, 0, -116.09 ), Vector(199.52, 239.45, -116.09), Vector(-309.96, 0, -116.09), Vector(0, 0, 1)}, 
  {Vector(295.05, -90.21, -147.8), Vector(262.9, 164.99, -89.7), Vector(-295.05, 90.21, -88.39), Vector(0.03, -0.22, 0.98)}
};

const static threeVectorIn_boolOut_t isCounterClockwise_case[3] = {
  {Vector(-0.98, 0.15, -0.13 ), Vector(0.95, 0.3, 0.03), Vector(-0.1, 0.2, 0.98), false},
  {Vector(-0.84, -0.55, 0.03), Vector(0.95, 0.3, 0.03), Vector(-0.1, 0.2, 0.98 ), true}, 
  {Vector(-127.3, 230.93, 0), Vector(-110.44, 239.45, 0), Vector(0, 0, -1 ), true}
};

const static twoVectorIn_vectorOut_t projectedVectorOntoPlane[2] = {
  {Vector(-185.37, 12.83, -111.44), Vector(-0.1, 0.2, 0.98), Vector(-194.09, 30.27, -25.98)}, 
  {Vector(-98.89, 134.4, -87.76), Vector(-0.1, 0.2, 0.98), Vector(-103.76, 144.145, -40.0055)}
};