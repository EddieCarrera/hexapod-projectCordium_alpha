#include "vector.hpp"

Vector::Vector(float x, float y, float z, std::string name, std::string id)
	: x(x), y(y), z(z)
{

}
/*******************************************************************************
 ******************************************************************************/
void Vector::newTrot(Vector *outputVector, float tranfMtrx[4][4], std::string name, std::string id)
{
	/* Format is:
  	[r00, r01, r02, tx] = r0
    [r10, r11, r12, ty] = r1
    [r20, r21, r22, tz] = r2
		[ 0 ,  0,   0,   1]
	*/
  outputVector->x = this->x*tranfMtrx[0][0] + this->y*tranfMtrx[0][1] + this->z*tranfMtrx[0][2] + tranfMtrx[0][3];
  outputVector->y = this->x*tranfMtrx[1][0] + this->y*tranfMtrx[1][1] + this->z*tranfMtrx[1][2] + tranfMtrx[1][3];
  outputVector->z = this->x*tranfMtrx[2][0] + this->y*tranfMtrx[2][1] + this->z*tranfMtrx[2][2] + tranfMtrx[2][3];
	outputVector->name = this->name;
	outputVector->id = this->id;
}
/*******************************************************************************
 ******************************************************************************/
void Vector::cloneTrot(Vector *outputVector, float tranfMtrx[4][4])
{
	this->newTrot(outputVector, tranfMtrx, this->name, this->id);
}
/*******************************************************************************
 ******************************************************************************/
void Vector::cloneShift(Vector *outputVector, float tx, float ty, float tz)
{
	outputVector->x = this->x + tx;
	outputVector->y = this->y + ty;
	outputVector->z = this->z + tz;
	outputVector->name = this->name;
	outputVector->id = this->id;
}
/*******************************************************************************
 ******************************************************************************/
void Vector::cloneTrotShift(Vector *outputVector, float tranfMtrx[4][4], float tx, float ty, float tz)
{
	this->cloneTrot(outputVector, tranfMtrx);
	this->cloneShift(outputVector, tx, ty, tz);
}
/*******************************************************************************
 ******************************************************************************/
void Vector::toMarkdownString(char* markdownString)
{
	std::snprintf(markdownString, strlen(markdownString), 
		"%s\r\n\r\n(x: %.2f, y: %.2f, z: %.2f)", 
		this->name.c_str(), this->x, this->y, this->z);
}