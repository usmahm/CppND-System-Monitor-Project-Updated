#include "processor.h"

using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  string line, key;
  float CPU_utilization;
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

        prev_idle_total_ = idle_total;
        prev_non_idle_total_ = non_idle_total;

        auto total = idle_total + non_idle_total;

        CPU_utilization = (total - idle_total) / total;


        return CPU_utilization;
      }
    }
  }

  return CPU_utilization;
}