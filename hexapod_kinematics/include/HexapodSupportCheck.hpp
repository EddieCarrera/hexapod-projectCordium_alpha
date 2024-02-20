#pragma once

#include "constants.hpp"

enum SupportCheck_reason_t {
  MIGHT_BE_STABLE_LESS,
  TOO_MANY_LEGS_OFF,
  RIGHT_LEGS_OFF,
  LEFT_LEGS_OFF,
  MIGHT_BE_STABLE_MORE
};

std::string SupportCheck_string[]
{
  "Might be stable.\nLess than three known legs are off the ground.",
  "Definitely Unstable.\nToo many legs off the floor.",
  "Definitely Unstable.\nAll right legs are off the floor.",
  "Definitely Unstable.\nAll left legs are off the floor.",
  "Might be stable.\nThree known legs are off the ground.\nOne is on opposite side of the other two.",
};

class HexapodSupportCheck
{
  // Static allows method to be called without reference to object
  public:
  static bool checkSupport(bool legsNamesoffGround[NUMBER_OF_LEGS], 
                           SupportCheck_reason_t *reason)
  {
    uint8_t count_legsOffGround = 0;

    for (uint8_t leg; leg < NUMBER_OF_LEGS; leg++){
      if (legsNamesoffGround[leg] == true){
        count_legsOffGround++;
      }
    }

    if (count_legsOffGround < 3){
      *reason = MIGHT_BE_STABLE_LESS;
      return false;
    }

    if (count_legsOffGround >= 4)
    {
      *reason = TOO_MANY_LEGS_OFF;
      return true;
    }

    // Leg count is exactly 3 at this point
    // TODO: Verify that this logic is intended
    if (legsNamesoffGround[rightFront] == true && 
        legsNamesoffGround[rightMiddle] == true && 
        legsNamesoffGround[rightBack] == true)
        {
          *reason = RIGHT_LEGS_OFF;
          return true;
        }    

    if (legsNamesoffGround[leftFront] == true && 
        legsNamesoffGround[leftMiddle] == true && 
        legsNamesoffGround[leftBack] == true)
        {
          *reason = LEFT_LEGS_OFF;
          return true;
        }

    *reason = MIGHT_BE_STABLE_LESS;
    return false;
  }
};