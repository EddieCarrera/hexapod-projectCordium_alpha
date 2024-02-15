#pragma once

#include "HexapodSupportCheck.hpp"
#include <stdio.h>
#include <string.h>
#include <string>

class IKMessage
{
  public:
  static std::string subject;
  static std::string body;

  public:
  void success(void){
    subject = "Success.";
    body = "All legs are on the floor.";
  }

  void successLegsOnAir(void){
    subject = "Success.";
    body = "But some legs won't reach target points on the ground.";
  }

  void noSupport(SupportCheck_reason_t reason){
    char buff[100];

    std::snprintf(buff, strlen(buff), "(Error: %d)", reason);

    subject = "Failure: No Support.";
    body = buff;
  }

  void badPoint(void){
    subject = "Failure: Bad Point.";
    body =  "At least one point would be shoved to the ground.";
  }

  void badLeg(std::string message){
    subject = "Failure: Bad leg.";
    body =  message;
  }

  void alphaNotInRange(std::string position, float alpha, float maxAngle)
  {
    char buff[100];

    std::snprintf(buff, strlen(buff), 
    "The alpha %.02f computed for %s leg is not within -%.02f < alpha < %0.2f", 
    alpha, position.c_str(), maxAngle, maxAngle);

    subject = "Failure: Alpha not within range";
    body = buff;
  }

  void initialized(void){
    subject = "Success.";
    body = "All legs are on the floor.";
  }    
};

class LegIKInfo 
{
  public:
  static std::string legPosition;
  static std::string message;
  static bool obtainedSolution;
  static bool reachedTarget;

  public:
  void targetReached(std::string position){
    char buff[100];

    legPosition = position;
    std::snprintf(buff, strlen(buff), 
      "Success! (%s)", position.c_str());
    message = buff;
    obtainedSolution = true;
    reachedTarget = true;
  }

  void targetNotReached(std::string position){
    char buff[100];

    legPosition = position;
    std::snprintf(buff, strlen(buff), 
      "Success! But this leg won't reach the target ground point. (%s)", position.c_str());
    message = buff;
    obtainedSolution = true;
    reachedTarget = false;
  }

  void blocked(std::string position){
    char buff[100];

    legPosition = position;
    std::snprintf(buff, strlen(buff), 
      "Failure. The ground is blocking the path. The target point can only be reached it by digging the ground. (%s)", position.c_str());
    message = buff;
    obtainedSolution = false;
    reachedTarget = true;
  }
  
  void femurTooLong(std::string position){
    char buff[100];

    legPosition = position;
    std::snprintf(buff, strlen(buff), 
      "Failure. Femur length too long. (%s)", position.c_str());
    message = buff;
    obtainedSolution = false;
    reachedTarget = false;
  }  

  void tibiaTooLong(std::string position){
    char buff[100];

    legPosition = position;
    std::snprintf(buff, strlen(buff), 
      "Failure. Tibia length too long. (%s)", position.c_str());
    message = buff;
    obtainedSolution = false;
    reachedTarget = false;
  }    

  void initialized(std::string position){
    char buff[100];

    legPosition = position;
    std::snprintf(buff, strlen(buff), 
      "Haven't solved anything yet. (%s)", position.c_str());
    message = buff;
    obtainedSolution = false;
    reachedTarget = false;
  }    
};