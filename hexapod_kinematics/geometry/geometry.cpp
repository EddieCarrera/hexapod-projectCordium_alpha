#include "geometry.hpp"

void cross(Vector *out, Vector a, Vector b)
{
  out->x = a.y * b.z - a.z * b.y;
  out->y = a.z * b.x - a.x * b.z;
  out->z = a.x * b.y - a.y * b.x;
}
/*******************************************************************************
 ******************************************************************************/
bool isCounterClockwise(Vector a, Vector b, Vector n){
    Vector outVector = Vector(0,0,0);
    cross(&outVector, b, n);
    return dot(a, outVector) > 0;
}
/*******************************************************************************
 ******************************************************************************/
void getNormalofThreePoints(Vector *normal, Vector a, Vector b, Vector c)
{
  Vector ab = Vector(0, 0, 0);
  Vector ac = Vector(0, 0, 0);
  Vector n = Vector(0, 0, 0);
  Vector unit_n = Vector(0, 0, 0);
  vectorFromTo(&ab, a, b);
  vectorFromTo(&ac, a, c);
  cross(&n, ab, ac);
  float len_n = vectorLength(n);
  scaleVector(normal, n, 1/len_n);
}
/*******************************************************************************
 ******************************************************************************/
float acosDegrees(float ratio)
{
  float thetaRadians = acos(ratio);
  if(isnan(thetaRadians))
  {
    // Fault catch
    return 0;
  }
  return toDegrees(thetaRadians);
}
/*******************************************************************************
 ******************************************************************************/
float angleOppositeOfLastSide(float a, float b, float c)
{
  if (a == 0 || b == 0) {
      // fault catch
      return 0;
  }

  float cosTheta = (a * a + b * b - c * c) / (2 * a * b);
  return acosDegrees(cosTheta);
}
/*******************************************************************************
 ******************************************************************************/
float angleBetween(Vector a, Vector b)
{
  if (vectorLength(a) == 0 || vectorLength(b) == 0) {
    return 0;
  }

  float cosTheta = dot(a, b)/sqrt(dot(a, a) * dot(b, b));
  return acosDegrees(cosTheta);
}
/*******************************************************************************
 ******************************************************************************/
void projectedVectorOntoPlane(Vector *projV, Vector vector, Vector planeNormal)
{
  Vector tempVector = Vector(0,0,0);
  float s = dot(vector, planeNormal) / dot(planeNormal, planeNormal);
  scaleVector(&tempVector, planeNormal, s);
  vectorFromTo(projV, tempVector, vector);
}
/*******************************************************************************
 ******************************************************************************/
void uniformMatrix4x4(float matrix[][4], float d)
{
	matrix[0][0] = d; matrix[0][1] = 0; matrix[0][2] = 0; matrix[0][3] = 0; 
	matrix[1][0] = 0; matrix[1][1] = d; matrix[1][2] = 0; matrix[1][3] = 0; 
	matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = d; matrix[2][3] = 0; 
	matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = d; 
}
/*******************************************************************************
 ******************************************************************************/
void dotMultiply4x4(float matrixOut[][4], float matrixA[][4], float matrixB[][4])
{
  for (uint32_t i = 0; i < 4; i++) {
      for (uint32_t j = 0; j < 4; j++) {
          matrixOut[i][j] = matrixA[i][j]*matrixB[i][j];
      }
  }
}
/*******************************************************************************
 ******************************************************************************/
void add4x4(float matrixOut[][4], float matrixA[][4], float matrixB[][4])
{
  for (uint32_t i = 0; i < 4; i++) {
      for (uint32_t j = 0; j < 4; j++) {
          matrixOut[i][j] = matrixA[i][j]+matrixB[i][j];
      }
  }
}
/*******************************************************************************
 ******************************************************************************/
void multiply4x4(float matrixOut[][4], float matrixA[][4], float matrixB[][4])
{
  for (uint32_t i = 0; i < 4; i++) {
      for (uint32_t j = 0; j < 4; j++) {
        matrixOut[i][j] = 
          matrixA[i][0] * matrixB[0][j] +
          matrixA[i][1] * matrixB[1][j] +
          matrixA[i][2] * matrixB[2][j] +
          matrixA[i][3] * matrixB[3][j];
      }
  }
}
/*******************************************************************************
 ******************************************************************************/
void tRotXmatrix(float matrixOut[][4], float theta, float tx, float ty, float tz)
{
  float s;
  float c;
  getSinCos(theta, &s, &c);
  /* Format is:
    [1,  0,  0,  tx],
    [0,  c, -s,  ty],
    [0,  s,  c,  tz],
    [0,  0,  0,  1]
  */
	matrixOut[0][0] = 1; matrixOut[0][1] = 0; matrixOut[0][2] = 0; 	matrixOut[0][3] = tx; 
	matrixOut[1][0] = 0; matrixOut[1][1] = c; matrixOut[1][2] = -s; matrixOut[1][3] = ty; 
	matrixOut[2][0] = 0; matrixOut[2][1] = s; matrixOut[2][2] = c; 	matrixOut[2][3] = tz; 
	matrixOut[3][0] = 0; matrixOut[3][1] = 0; matrixOut[3][2] = 0; 	matrixOut[3][3] = 1; 
}
/*******************************************************************************
 ******************************************************************************/
void tRotYmatrix(float matrixOut[][4], float theta, float tx, float ty, float tz)
{
  float s;
  float c;
  getSinCos(theta, &s, &c);
  /* Format is:
    [c,  0,  s,  tx],
    [0,  1,  0,  ty],
    [-s, 0,  c,  tz],
    [0,  0,  0,  1]
  */
	matrixOut[0][0] = c;  matrixOut[0][1] = 0; matrixOut[0][2] = s; matrixOut[0][3] = tx; 
	matrixOut[1][0] = 0;  matrixOut[1][1] = 1; matrixOut[1][2] = 0; matrixOut[1][3] = ty; 
	matrixOut[2][0] = -s; matrixOut[2][1] = 0; matrixOut[2][2] = c; matrixOut[2][3] = tz; 
	matrixOut[3][0] = 0;  matrixOut[3][1] = 0; matrixOut[3][2] = 0; matrixOut[3][3] = 1; 
}
void tRotZmatrix(float matrixOut[][4], float theta, float tx, float ty, float tz)
{
  float s;
  float c;
  getSinCos(theta, &s, &c);
  /* Format is:
    [c, -s, 0,  tx],
    [s, c,  0,  ty],
    [0, 0,  1,  tz],
    [0, 0,  0,  1]
  */
	matrixOut[0][0] = c; matrixOut[0][1] = -s; matrixOut[0][2] = 0; matrixOut[0][3] = tx; 
	matrixOut[1][0] = s; matrixOut[1][1] = c;  matrixOut[1][2] = 0; matrixOut[1][3] = ty; 
	matrixOut[2][0] = 0; matrixOut[2][1] = 0;  matrixOut[2][2] = 1; matrixOut[2][3] = tz; 
	matrixOut[3][0] = 0; matrixOut[3][1] = 0;  matrixOut[3][2] = 0; matrixOut[3][3] = 1; 
}
/*******************************************************************************
 ******************************************************************************/
void tRotXYZmatrix(float matrixOut[][4], float xTheta, float yTheta, float zTheta)
{
  float rx[4][4] = {0};
  float ry[4][4] = {0};
  float rz[4][4] = {0};
  float rxy[4][4] = {0};
  tRotXmatrix(rx, xTheta);
  tRotYmatrix(ry, yTheta);
  tRotZmatrix(rz, zTheta);
  multiply4x4(rxy, rx, ry);
  multiply4x4(matrixOut, rxy, rz);
}
/*******************************************************************************
 ******************************************************************************/
void matrixToAlignVectorAtoB(float matrixOut[][4], Vector a, Vector b)
{
  Vector v = Vector(0,0,0);
  float vx[4][4] = {0};
  float vx2[4][4] = {0};
  float dMatrix[4][4] = {0};
  float dvx2[4][4] = {0};
  float temp[4][4] = {0};

  cross(&v, a, b);
  float s = vectorLength(v);
  // When the angle between a and b is zero or 180 degrees
  // then cross product is 0, R = I
  if (s == 0) {
    memcpy (matrixOut, IDENTITY_MATRIX_4x4, 4*4*sizeof(float));
  }

  float c = dot(a, b);
  skew(vx, v);
  float d = (1 - c) / (s * s);
  multiply4x4(vx2, vx, vx);
  uniformMatrix4x4(dMatrix, d);
  dotMultiply4x4(dvx2, vx2, dMatrix);
  add4x4(temp, IDENTITY_MATRIX_4x4, vx);
  add4x4(matrixOut, temp, dvx2);
} 