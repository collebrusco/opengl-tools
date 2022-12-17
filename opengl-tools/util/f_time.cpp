//
//  f_time.cpp
//  opengl-tools
//
//  Created by Frank Collebrusco on 5/31/22.
//

#include "f_time.h"



#include <chrono>
#include <ctime>

static std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
static auto duration = now.time_since_epoch();
static auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
static double epoch_to_launch_nanos = nanoseconds.count();

static double nanos(){
    now = std::chrono::system_clock::now();
    duration = now.time_since_epoch();
    nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    return (double)nanoseconds.count() - epoch_to_launch_nanos;
}
static double stopwatch_start_time = 0;
static double stopwatch_stop_time = 0;
static bool stopwatch_running = false;
double ftime::since_launch(ftime::TimeUnit u){
    return nanos() / (double)u;
}
void ftime::stopwatch_start(){
    stopwatch_running = true;
    stopwatch_start_time = nanos();
}
double ftime::stopwatch_stop(ftime::TimeUnit u){
    stopwatch_running = false;
    stopwatch_stop_time = nanos();
    return (stopwatch_stop_time - stopwatch_start_time) / (double)u;
}
double ftime::stopwatch_read(ftime::TimeUnit u){
    if (stopwatch_running){
        return (nanos() - stopwatch_start_time) / (double)u;
    }
    return (stopwatch_stop_time - stopwatch_start_time) / (double)u;
}



