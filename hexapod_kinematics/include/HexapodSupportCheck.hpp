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
  static bool checkSupport(POSITION_NAME_TO_ID_MAP legPosition, 
                           SupportCheck_reason_t *reason)
  {

  }

};