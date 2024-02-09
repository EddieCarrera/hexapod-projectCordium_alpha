#pragma once

#include "vector.hpp"
#include <math.h>

const float PI = 3.14159265358979323846;

static float IDENTITY_MATRIX_4x4[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};
/*******************************************************************************
 ******************************************************************************/
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
inline bool isCounterClockwise(Vector a, Vector b, Vector n){
    Vector outVector = Vector(0,0,0);
    cross(&outVector, b, n);
    return dot(a, outVector) > 0;
}
inline void vectorFromTo(Vector *out, Vector a, Vector b){
    out->x = b.x - a.x;
    out->y =  b.y - a.y;
    out->z = b.z - a.z;
}
inline void scaleVector(Vector *out, Vector v, float d){
    out->x = d * v.x;
    out->y = d * v.y;
    out->z = d * v.z;
}
inline void addVectors(Vector *out, Vector a, Vector b){
    out->x = a.x + b.x;
    out->y = a.y + b.y;
    out->z = a.z + b.z;
}
inline void getUnitVector(Vector *out, Vector v){
    scaleVector(out, v, 1 / vectorLength(v));
}
inline void getSinCos(float degrees, float *sinRad, float *cosRad){
    *sinRad = sin(toRadians(degrees));
    *cosRad = cos(toRadians(degrees));
}
inline void skew(float matrix[][4], Vector p)
{
	/* Format is:
    [0,   -p.z,  p.y, 0]
    [p.z,  0,   -p.x, 0]
    [-p.y, p.x,  0,   0]
    [0,    0,    0,   1]
	*/
	matrix[0][0] = 0; 		matrix[0][1] = -p.z; 	matrix[0][2] = p.y; 	matrix[0][3] = 0; 
	matrix[1][0] = p.z;		matrix[1][1] = 0; 		matrix[1][2] = -p.x; 	matrix[1][3] = 0; 
	matrix[2][0] = -p.y; 	matrix[2][1] = p.x; 	matrix[2][2] = 0; 		matrix[2][3] = 0; 
	matrix[3][0] = 0; 		matrix[3][1] = 0; 		matrix[3][2] = 0; 		matrix[3][3] = 1; 
}
/*******************************************************************************
 ******************************************************************************/
void cross(Vector *out, Vector a, Vector b);
void getNormalofThreePoints(Vector *normal, Vector a, Vector b, Vector c);
float acosDegrees(float ratio);
float angleOppositeOfLastSide(float a, float b, float c);
float angleBetween(Vector a, Vector b);
void projectedVectorOntoPlane(Vector *projV, Vector vector, Vector planeNormal);
void uniformMatrix4x4(float matrix[][4], float d);
void dotMultiply4x4(float matrixOut[][4], float matrixA[][4], float matrixB[][4]);
void add4x4(float matrixOut[][4], float matrixA[][4], float matrixB[][4]);
void multiply4x4(float matrixOut[][4], float matrixA[][4], float matrixB[][4]);
void tRotXmatrix(float matrixOut[][4], float theta, float tx = 0, float ty = 0, float tz = 0);
void tRotYmatrix(float matrixOut[][4], float theta, float tx = 0, float ty = 0, float tz = 0);
void tRotZmatrix(float matrixOut[][4], float theta, float tx = 0, float ty = 0, float tz = 0);
void tRotXYZmatrix(float matrixOut[][4], float xTheta, float yTheta, float zTheta);
void matrixToAlignVectorAtoB(float matrixOut[][4], Vector a, Vector b); 
