#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  long hours=0;
  long mins=0;
  long secs=0;
  
    hours=seconds/3600;
    mins=(seconds-(hours*3600))/60;
    if(seconds<60){
      secs=seconds;
    }
  else{
  
    secs=seconds-(hours*3600)-(mins*60);
  }
    
  std::stringstream t;
  t<<std::setw(2)<< std::setfill('0')<<hours<<":"<<std::setw(2)<< std::setfill('0')<<mins<<":"<<std::setw(2)<< std::setfill('0')<<secs;
  
string T=t.str();
  return T;
}