#pragma once

#include "../vector/vector.hpp"

typedef struct {
  Vector vectorA;
  Vector vectorB;
  float angleResult;
} twoVectorIn_floatOut_t;

typedef struct {
  Vector vectorA;
  Vector vectorB;
  Vector vectorResult;
} twoVectorIn_vectorOut_t;

typedef struct {
  float sideA;
  float sideB;
  float sideC;
  float angleResult;
} threeFloatIn_floatOut_t;

typedef struct {
  Vector vectorA;
  Vector vectorB;
  Vector vectorC;
  Vector vectorResult;
} threeVectorIn_vectorOut_t;

typedef struct {
  Vector vectorA;
  Vector vectorB;
  Vector vectorC;
  bool boolResult;
} threeVectorIn_boolOut_t;
