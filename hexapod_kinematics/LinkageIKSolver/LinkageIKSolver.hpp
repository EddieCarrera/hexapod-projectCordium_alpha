#pragma once

/* *

ALIASES:
    p0: bodyContactPoint (local)
    p1: coxaPoint (local)
    p2: femurPoint (local)
    p3: footTipPoint (local)

           p2x'
           /
          /          GIVEN:
         * p2         * (coxia) distance from p0 to p1
        /|            * (femur) distance from p1 to p2
       / |            * (tibia) distance from p2 to p3
p0  p1/  |            * (summa) distance from p0 to p3
 *---*   | ---> p1x'_  * rho: angle between
  \   \  |                 -> p0 to p1 and p0 to p3
    \  \ |            * p0 is (0, 0, 0)
      \ \|            * p0 to p1 vector is inline with legXaxis
        * p3
                    INTERMEDIATE:
legZaxis              * (pars) distance from p1 to p3
 ^                    * theta: angle between
 |                          -> p1 to p2 and p1 and p3
 * - > legXaxis       * phi: angle between
                            -> p1 to p3 and p1 to p1x'_ (legXaxis)
                      * epsi: angle between
                            -> p2 to p1 and p2 to p3

FIND: (counter clockwise is positive)
  * beta: Angle betweenlegXaxis and p1 to p2
          beta > 0 if p1 to p2 is above legXaxis
          beta < 0 if p1 to p2 is below the legXaxis
  * gamma: Angle between p1 to p2 and axis perpendicular to p1 p2

EXAMPLE: When p0, p2, p3, and p3 are configured this way then:
    * p2 to p3z' axis is 180 degrees wrt legZaxis
    * beta = 0
    * gamma = +90

p0   p1   p2   p3
*----*----*----*
          |
          |
          V p3z'

 * */
#include "IKinfo.hpp"
#include "vector.hpp"
#include "geometry.hpp"

class LinkageIKSolver
{
  typedef struct {
    Vector legXaxis;
    Vector parsVector;
  } linkIK_vectors;

  typedef struct {
    Vector bodyContactPoint;
    Vector coxiaPoint;
    Vector targetFootTipPoint;
  } linkIK_points;

  typedef struct {
    float coxia;
    float femur;
    float tibia;
    float summa;
    float pars;
  } linkIK_dimensions;

  typedef struct {
    float beta; 
    float gamma;
    float rho;
  } linkIK_angles;

  public:
  linkIK_vectors vectors = {
    Vector(1, 0, 0, "legXaxis"), 
    Vector(0, 0, 0, "parsVector") 
  };
  linkIK_points points = {
    Vector(0, 0, 0, "bodyContactPoint"), 
    Vector(0, 0, 0, "coxiaPoint"), 
    Vector(0, 0, 0, "targetFootTipPoint")
  };
  linkIK_dimensions dimensions = {0};
  linkIK_angles angles = {0};
  LegIKInfo info;

  /* Constructor */
	public:
	LinkageIKSolver(std::string legPosition);

	/* Methods */
	void solve(linkIK_dimensions inputDimensions, linkIK_angles inputAngles);

  private:
  void _computeTargetFootTipPoint(Vector *out);
  void _handleCaseTriangleCanForm(void);
  void _handleEdgeCase(void);
};
