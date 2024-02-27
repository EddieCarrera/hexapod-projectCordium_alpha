#pragma once

#include "LinkageIKSolver.hpp"
#include "HexapodSupportCheck.hpp"
#include "IKinfo.hpp"
#include "constants.hpp"
#include "geometry.hpp"

/* * *

.......
Given:
.......

{}. Dimensions of each leg { femur, tibia, gamma }
[] bodyContactPoints
[] groundContactPoints
   - there are two lists which contains six items each. One item for each leg.
{} axes { xAxis, zAxis }
   xAxis and zAxis of the rotated hexapod's local coordinate frame wrt
   world coordinate frame.

.......
Definition:
.......

bodyContactPoint (x, y, z)
- The point in 3d space which is a vertex of the hexagon.
  This is where the leg is in contact with the body of the hexapod.

groundContactPoint (x, y, z)
- The point in 3d space which we want the foot tip of
  the leg to be. Where the leg is in contact with the ground plane of the world.

.......
Find:
.......

18 angles that represent the pose of the hexapod. Three angles for each leg.
    {
      rightMiddle: { alpha, beta, gamma },
      ...
      rightBack: { alpha, beta, gamma },
    }

    If no solution is found, make sure to explain why.

.......
Algorithm:
.......

If one of the vertices is below the ground z < 0,
then there is no solution. Early exit.

For each leg:
    1. Derive a few properties about the leg given what you already know
       which you'd later (see computeInitialProperties() for details )

       This includes the coxiaPoint. If this coxiaPoint is below the ground
        - then there is no solution. Early exit.

    2. Compute the alpha of this leg. see (computeAlpha())
       If alpha is not within range, then there is no solution. Early exit.

    3. Solve for beta and gamma of this leg (see LegIKSolver module)
      If a problem was encountered within this module, then there is no solution. Early exit.
      If the beta and gamma are not within range, then there is no solution, early exit.

    4. Sometimes the LegIKSolver module would return a solution where the leg
       would not reach the target ground contact point. (this leg would be on the air)
       If the combination of the legs in the air would produce an unstable pose
       (e.g 4 legs are in the air or all left legs are in the air)
       Then there is no solution. Early exit.
       (see also HexapodSupportChecker)

    If no problems are encountered, we have found a solution! Return!

* * */

class IKSolver {

  typedef struct {
    float coxia;
    float femur;
    float tibia;
  } legDimensions_t;

  typedef struct {
    Vector xAxis;
    Vector yAxis;
    Vector zAxis;
  } axis_t;

  typedef struct {
    Vector bodyContactPoints[NUMBER_OF_LEGS];
    Vector groundContactPoints[NUMBER_OF_LEGS];
    axis_t axes;
    legDimensions_t legDimensions;
  } params_t; 

  typedef struct {
    float alpha;
    float beta;
    float gamma;
  } poseAngles_t;

  params_t params;
  poseAngles_t partialPose;
  poseAngles_t pose;
  bool foundSolution = false;
  bool legPositionsOffGround[NUMBER_OF_LEGS] = {false}; // mapping of POSITION_NAME_TO_ID_MAP
  IKMessage message;

  /* Constructor */
  public:
  IKSolver(params_t params);

  /* Methods */
  void solve(params_t parameters);

  private:
  bool _hasLegsOffGround(void);
  bool _hasNoMoreSupport(bool legPositionsOffGround[NUMBER_OF_LEGS]);
  void _handleBadPoint(void);
  bool _hasBadVertex(Vector bodyContactPoints[NUMBER_OF_LEGS]);
  void _finalizeFailure(IKMessage message);
  void _finalizeSuccess(void);
};

/* * *

computeInitialLegProperties()

.......
Given:
.......

1. pB : bodyContactPoint in 3d space
2. pG : groundContactPoint in 3d space
3. coxia: distance from pB to pC
4. zAxis: The vector normal to the hexapodBodyPlane

.......
Find:
.......

1. pC : coxiaPoint in 3d space
2. coxiaVector: the vector from pB to Pc with a length of one
3. coxiaUnitVector: A vector with the length of one
    pointing at the direction of the unit vector
4. rho: The angle made by pC, pB and pG, with pB at the center
5. summa: The distance from pB to pG

pB   pC
 *---* -------- hexapodBodyPlane
  \   \
   \   *
    \  /
      * ------- groundPlane
      pG

.......
Idea:
.......

1. Get the vector from pB to pG (bodyToFootVector)
2. Project that vector to the hexapodBodyPlane (coxiaDirectionVector)
   The direction of this vector is the direction of
   coxiaVector and coxiaUnitVector

   And with a little bit of geometry you derive everything you need.

 * * */
typedef struct {
  Vector coxiaUnitVector;
  Vector coxiaVector;
  Vector coxiaPoint;
  float rho;
  float summa;
} initialLegProperties_t;

initialLegProperties_t computeInitialLegProperties(
  Vector bodyContactPoints[NUMBER_OF_LEGS], 
  Vector groundContactPoints[NUMBER_OF_LEGS], 
  Vector zAxis, 
  float coxia);

