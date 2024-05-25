#include "processor.h"

using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  float CPU_utilization;

  auto prev_total = prev_idle_total_ + prev_non_idle_total_;

  auto idle_nonidle_time = GetIdlenNoneIdleTime();

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

std::array<double, 2> Processor::GetIdlenNoneIdleTime() {
  string line, key;
  std::array<double, 2> idle_nonidle_time;
  double usertime, nicetime, systemtime, idletime, iowait, irq, softirq, steal, guest, guestnice;

  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      std::stringstream ss(line);
      ss >> key;

      if (key == "cpu") {
        ss >> usertime >> nicetime >> systemtime >> idletime >> iowait >> irq >> softirq >> steal >> guest >> guestnice;

        auto idle_total = idletime + iowait;
        auto non_idle_total = usertime + nicetime + systemtime + irq + softirq + steal;

        idle_nonidle_time[0] = idle_total;
        idle_nonidle_time[1] = non_idle_total;

        return idle_nonidle_time;
      }
    }
  }

  return idle_nonidle_time;
}

// Processor::Processor() {
//   auto idle_nonidle_time = GetIdlenNoneIdleTime();

//   prev_idle_total_ = idle_nonidle_time[0];
//   prev_non_idle_total_ = idle_nonidle_time[1];
// }