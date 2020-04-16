#ifndef PROCESS_H
#define PROCESS_H

#include <string>

//#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int id);
  int Pid();                               // TODO: See src/process.cpp
  void User_();
  std::string User();                      // TODO: See src/process.cpp
  void Command_();
  std::string Command();   
  // TODO: See src/process.cpp
  void  Cpu_Utilization();
  float CpuUtilization();                  // TODO: See src/process.cpp
  void Ram_();
  std::string Ram();                       // TODO: See src/process.cpp
  void Up_Time();
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int pid_;
  float cpu_util;
  std::string command_;
  std::string ram_;
  std::string user_;
  long int up_time;
};

#endif