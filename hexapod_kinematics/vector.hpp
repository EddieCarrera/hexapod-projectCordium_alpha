#pragma once

#include <stdint.h>
#include <string>

class Vector {

	private:
	/* Variables */
	float x;
	float y;
	float z;
	std::string name;
	std::string id;

	public:


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
	void newTrot(Vector *outputVector, float transformMatrix[4][4], std::string name, std::string id);
	
	void cloneTrot(Vector *outputVector, float transformMatrix[4][4]);
	void cloneShift(Vector *outputVector, float x, float y, float z);
	void cloneTrotShift(Vector *outputVector, float transformMatrix[4][4], float x, float y, float z);

	private:


};