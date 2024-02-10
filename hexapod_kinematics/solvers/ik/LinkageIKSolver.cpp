#include "../../include/LinkageIKSolver.hpp"

LinkageIKSolver::LinkageIKSolver(std::string legPosition)
{
  this->info.initialized(legPosition);

}
/*******************************************************************************
 ******************************************************************************/
void LinkageIKSolver::solve(linkIK_dimensions inputDimensions, linkIK_angles inputAngles)
{
  Vector targetFootTipPoint = Vector(0, 0, 0);
  Vector parsVector = Vector(0, 0, 0);

  this->angles.rho = inputAngles.rho;
  this->dimensions = inputDimensions;
  Vector coxiaPoint = Vector(inputDimensions.coxia, 0, 0, "coxiaPoint");
  this->_computeTargetFootTipPoint(&targetFootTipPoint);

  vectorFromTo(&parsVector, coxiaPoint, targetFootTipPoint);
  float pars = vectorLength(parsVector);

  this->dimensions.pars = pars;
  this->points.coxiaPoint = coxiaPoint;
  this->points.targetFootTipPoint = targetFootTipPoint;
  this->vectors.parsVector = parsVector;

  isTriangle(pars, inputDimensions.femur, inputDimensions.tibia)
    ? this->_handleCaseTriangleCanForm()
    : this->_handleEdgeCase();  
}
/*******************************************************************************
 ******************************************************************************/
void LinkageIKSolver::_computeTargetFootTipPoint(Vector *out)
{
  float summa = this->dimensions.summa;
  float rho = this->angles.rho;
  float px = summa*cos(toRadians(rho));
  float pz = -summa*sin(toRadians(rho));
  out->x = px;
  out->y = 0;
  out->z = pz;
  out->name = "targetLocalFootTipPoint";
}
/*******************************************************************************
 ******************************************************************************/
void LinkageIKSolver::_handleCaseTriangleCanForm(void)
{
  float femur = this->dimensions.femur;
  float pars = this->dimensions.pars;
  float tibia = this->dimensions.tibia;
  float targetFootTipPoint_z = this->points.targetFootTipPoint.z;

  float theta = angleOppositeOfLastSide(femur, pars, tibia);
  float phi = angleBetween(this->vectors.parsVector, this->vectors.legXaxis);
  float beta = targetFootTipPoint_z < 0 ? theta - phi : theta + phi;
  float epsi = angleOppositeOfLastSide(femur, tibia, pars);
  float femurPointz = femur*sin(toRadians(beta));

  this->angles.beta = beta;
  
  if (targetFootTipPoint_z > femurPointz) {
      this->info.blocked(this->info.legPosition);
      return;
  }          

  this->angles.gamma = epsi - 90;
  this->info.targetReached(this->info.legPosition);
}
/*******************************************************************************
 ******************************************************************************/
void LinkageIKSolver::_handleEdgeCase(void)
{
  float femur = this->dimensions.femur;
  float pars = this->dimensions.pars;
  float tibia = this->dimensions.tibia;

  if (pars + tibia < femur) {
      this->info.femurTooLong(this->info.legPosition);
      return;
      // Fault catch
  }

  if (pars + femur < tibia) {
      this->info.tibiaTooLong(this->info.legPosition);
      return;
      // Fault catch
  }  

  // then femur + tibia < pars
  //
  // p0 *---* p1     * stretch to try to reach target
  //         \       * gamma:
  //          * p2      => 90: stretch, 0: curl down, 180: curl up
  //           \
  //            * p3 (actual when stretched)
  //
  //              * targetp3
  //

  this->angles.beta = -angleBetween(this->vectors.parsVector,
                                    this->vectors.legXaxis);
  this->angles.gamma = 90;                                    
  this->info.targetNotReached(this->info.legPosition);
}
/*******************************************************************************
 ******************************************************************************/