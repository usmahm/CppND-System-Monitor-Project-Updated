#include "processor.h"

using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  float CPU_utilization;

  auto prev_total = prev_idle_total_ + prev_non_idle_total_;

  auto idle_nonidle_time = LinuxParser::GetIdlenNoneIdleTime();

  auto idle_total = idle_nonidle_time[0];
  auto non_idle_total = idle_nonidle_time[1];
  auto total = idle_total + non_idle_total;

  auto total_diff = total - prev_total;
  auto idle_diff = idle_total - prev_idle_total_;

  CPU_utilization = (total_diff - idle_diff) / total_diff;

  prev_idle_total_ = idle_total;
  prev_non_idle_total_ = non_idle_total;

  return CPU_utilization;
}

// Processor::Processor() {
//   auto idle_nonidle_time = GetIdlenNoneIdleTime();

//   prev_idle_total_ = idle_nonidle_time[0];
//   prev_non_idle_total_ = idle_nonidle_time[1];
// }