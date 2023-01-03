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
static double global_stopwatch_start_time = 0;
static double global_stopwatch_stop_time = 0;
static bool global_stopwatch_running = false;
double ftime::since_launch(ftime::TimeUnit u){
    return nanos() / (double)u;
}
void ftime::global_stopwatch_start(){
    global_stopwatch_running = true;
    global_stopwatch_start_time = nanos();
}

double ftime::global_stopwatch_stop(ftime::TimeUnit u){
    global_stopwatch_running = false;
    global_stopwatch_stop_time = nanos();
    return (global_stopwatch_stop_time - global_stopwatch_start_time) / (double)u;
}
double ftime::global_stopwatch_read(ftime::TimeUnit u){
    if (global_stopwatch_running){
        return (nanos() - global_stopwatch_start_time) / (double)u;
    }
    return (global_stopwatch_stop_time - global_stopwatch_start_time) / (double)u;
}

double ftime::global_stopwatch_stopstart(ftime::TimeUnit u){
    double dt = ftime::global_stopwatch_stop(NANOSECONDS);
    ftime::global_stopwatch_start();
    return dt / (double)u;
}

// ********************************STOPWATCH OBJ DEFNS********************************

ftime::StopWatch::StopWatch(){
    _reset = true;
    auto _now = std::chrono::system_clock::now();
    auto _duration = _now.time_since_epoch();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_duration);
    unit = NANOSECONDS;
    epoch_to_construct_nanos = ns.count();
}

ftime::StopWatch::StopWatch(TimeUnit u){
    _reset = true;
    unit = u;
    auto _now = std::chrono::system_clock::now();
    auto _duration = _now.time_since_epoch();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_duration);
    epoch_to_construct_nanos = ns.count();
}

void ftime::StopWatch::setUnit(TimeUnit u){
    unit = u;
}

void ftime::StopWatch::start(){
    if (_reset){
        _reset = false;
        stopwatch_start_time = nanos();
    }
    _running = true;
}

void ftime::StopWatch::reset(){
    _reset = true;
}

bool ftime::StopWatch::running(){
    return _running;
}

double ftime::StopWatch::read(){
    return this->read(unit);
}

double ftime::StopWatch::read(TimeUnit u){
    if (_running){
        return (nanos() - global_stopwatch_start_time) / (double)u;
    }
    return (global_stopwatch_stop_time - global_stopwatch_start_time) / (double)u;
}

double ftime::StopWatch::stop(){
    return this->stop(unit);
}

double ftime::StopWatch::stop(TimeUnit u){
    if (_running){
        _running = false;
        stopwatch_stop_time = nanos();
    }
    return (stopwatch_stop_time - stopwatch_start_time) / (double)u;
}

void ftime::StopWatch::reset_start(){
    this->reset();
    this->start();
}

double ftime::StopWatch::stop_reset(){
    return this->stop_reset(unit);
}

double ftime::StopWatch::stop_reset(TimeUnit u){
    double r = this->stop(u);
    this->reset();
    return r;
}

double ftime::StopWatch::stop_reset_start(){
    return this->stop_reset_start(unit);
}

double ftime::StopWatch::stop_reset_start(TimeUnit u){
    double r = this->stop_reset(u);
    this->start();
    return r;
}
