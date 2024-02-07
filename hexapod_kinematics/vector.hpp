#pragma once

#include <stdint.h>
#include <string.h>
#include <string>

class Vector {

	/* Variables */
	float x;
	float y;
	float z;
	std::string name;
	std::string id;

	/* Constructor */
	public:
	Vector(float x, float y, float z, std::string name, std::string id);

	/* Methods */
	public:
	/**
	 * Given point `point` location wrt a local axes coordinate frame
	 * find point in a global axes coordinate frame where the local 
	 * axes wrt the global frame is defined by parameter transformMatrix 
	 * */
	void newTrot(Vector *outputVector, float tranfMtrx[4][4], std::string name, std::string id);
	
	void cloneTrot(Vector *outputVector, float tranfMtrx[4][4]);
	void cloneShift(Vector *outputVector, float tx, float ty, float tz);
	void cloneTrotShift(Vector *outputVector, float tranfMtrx[4][4], float tx, float ty, float tz);
	void toMarkdownString(char *markdownString);
};