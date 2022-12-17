//
//  FTime.cpp
//  opengl-tools
//
//  Created by Frank Collebrusco on 5/31/22.
//

#include "FTime.h"



#include <chrono>
#include <ctime>


static std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
static auto duration = now.time_since_epoch();
static auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
static double epoch_to_launch_nanos = nanoseconds.count();


double nanos(){
    now = std::chrono::system_clock::now();
    duration = now.time_since_epoch();
    nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    return (double)nanoseconds.count() - epoch_to_launch_nanos;
}
double micros(){
    return nanos() / 1000;
}
double millis(){
    return nanos() / 1000000;
}
double seconds(){
    return nanos() / 1000000000;
}





