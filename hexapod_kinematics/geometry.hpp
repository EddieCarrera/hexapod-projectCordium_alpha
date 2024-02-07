#pragma once

#include "vector.hpp"
#include <math.h>

const float PI = 3.141592;

inline float toDegrees(float thetaRadians){
    return (thetaRadians * 180)/PI;
}
inline float toRadians(float thetaDegrees){
    return (thetaDegrees * PI)/180;
}
inline bool isTriangle(float a, float b, float c){
    return a + b > c && a + c > b && b + c > a;
}
inline float dot(Vector a, Vector b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline float vectorLength(Vector v){
    return sqrt(dot(v,v));
}
