#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  string up_hr, up_min, up_sec;

  up_hr = to_string(seconds / 3600);

  int rem =  seconds % 3600;

  up_min = to_string(rem / 60);
  up_sec = to_string(rem % 60);

  up_hr.insert(0, 2 - up_hr.length(), '0');
  up_min.insert(0, 2 - up_min.length(), '0');
  up_sec.insert(0, 2 - up_sec.length(), '0');

  string formatted_time = up_hr + ':' + up_min + ":" + up_sec;
  return formatted_time;
}