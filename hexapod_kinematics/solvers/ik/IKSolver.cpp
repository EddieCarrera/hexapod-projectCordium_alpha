#include "../../include/IKSolver.hpp"

IKSolver::IKSolver(params_t params)
  : params(params)
{
  this->message.initialized();
}
/*******************************************************************************
 ******************************************************************************/
void IKSolver::solve(params_t parameters)
{
  this->params = parameters;

  if (this->_hasBadVertex(parameters.groundContactPoints)){
    return; // vs. return this?
  }

  const legDimensions_t legDimensions = parameters.legDimensions;

  for (uint8_t leg = 0; leg < NUMBER_OF_LEGS; leg++)
  {
    std::string legPosition = POSITION_NAMES_LIST[leg];

  


  }

}
/*******************************************************************************
 ******************************************************************************/
bool IKSolver::_hasLegsOffGround(void)
{
  for (uint8_t leg = 0; leg < NUMBER_OF_LEGS; leg++){
    if (this->legPositionsOffGround[leg] == true){return true;}
  }
  return false;
}
/*******************************************************************************
 ******************************************************************************/
bool IKSolver::_hasNoMoreSupport(bool legPositionsOffGround[NUMBER_OF_LEGS])
{
  SupportCheck_reason_t reason;
  bool no_support;

  for (uint8_t leg = 0; leg < NUMBER_OF_LEGS; leg++){
    this->legPositionsOffGround[leg] = legPositionsOffGround[leg];
  }

  no_support = HexapodSupportCheck::checkSupport(&(this->legPositionsOffGround[NUMBER_OF_LEGS]), &reason);

  if (no_support){
    this->message.noSupport(reason);
    return true;
  }
  return false;
}
/*******************************************************************************
 ******************************************************************************/
bool IKSolver::_hasBadVertex(Vector bodyContactPoints[NUMBER_OF_LEGS])
{
  for (uint8_t leg = 0; leg < NUMBER_OF_LEGS; leg++){
    if (bodyContactPoints[leg].z < 0){
      this->message.badPoint();
      return true;
    }
  }
  return false;
}
/*******************************************************************************
 ******************************************************************************/
void IKSolver::_finalizeSuccess(void)
{
  this->pose = this->partialPose;
  this->foundSolution = true;
  if (!this->_hasLegsOffGround()){
    this->message.success();
    return;
  }
  this->message.successLegsOnAir();
}
/*******************************************************************************
 ******************************************************************************/
void computeInitialLegProperties(initialLegProperties_t *out, Vector bodyContactPoint, 
                                 Vector groundContactPoint, Vector zAxis, float coxia)
{
  Vector bodyToFootVector = Vector(0, 0, 0);
  Vector coxiaDirectionVector = Vector(0, 0, 0);

  vectorFromTo(&bodyToFootVector, bodyContactPoint, groundContactPoint);

  projectedVectorOntoPlane(&coxiaDirectionVector, bodyToFootVector, zAxis);
  getUnitVector(&(out->coxiaUnitVector), coxiaDirectionVector);
  scaleVector(&(out->coxiaVector), out->coxiaUnitVector, coxia);

  addVectors(&(out->coxiaPoint), bodyContactPoint, out->coxiaVector);

  out->rho = angleBetween(out->coxiaUnitVector, bodyToFootVector);
  out->summa = vectorLength(bodyToFootVector);
}
/*******************************************************************************
 ******************************************************************************/
float computeAlpha(Vector coxiaVector, float legXaxisAngle, Vector xAxis, Vector zAxis)
{
  bool sign = isCounterClockwise(coxiaVector, xAxis, zAxis) ? -1 : 1;
  float alphaWrtHexapod = sign * angleBetween(coxiaVector, xAxis);
  float alpha = (alphaWrtHexapod - legXaxisAngle) % 360;

  if (alpha > 180) {
      return alpha - 360;
  }
  if (alpha < -180) {
      return alpha + 360;
  }

  // ❗❗❗THIS IS A HACK ❗❗❗
  // THERE IS A BUG HERE SOMEWHERE, FIND IT
  if (alpha == 180 || alpha == -180) {
      return 0;
  }

  return alpha;
}