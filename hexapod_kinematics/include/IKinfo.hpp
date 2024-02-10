#pragma once

#include <stdio.h>
#include <string.h>
#include <string>

class IKMessage
{
  std::string subject;
  std::string body;

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