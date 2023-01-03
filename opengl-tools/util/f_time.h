//
//  f_time.h
//  workspace 2.0
//
//  Created by Frank Collebrusco on 5/24/22.
//

#ifndef f_time_h
#define f_time_h

#include <chrono>
#include <ctime>
namespace ftime {
enum TimeUnit {
    SECONDS = 1000000000,
    MILLISECONDS = 1000000,
    MICROSECONDS = 1000,
    NANOSECONDS = 1
};
double since_launch(TimeUnit);          // return time since launch
// stopwatch
void global_stopwatch_start();                 // start stopwatch
double global_stopwatch_stop(ftime::TimeUnit); // stop & read stopwatch
double global_stopwatch_read(ftime::TimeUnit); // read stopwatch, safe even after stop
double global_stopwatch_stopstart(ftime::TimeUnit); // stop, read, and restart stopwatch.
                                             // do this at the end of a loop to read dt

// construct these as little simple timers
// init with time unit, default is nanoseconds
class StopWatch {
private:
    TimeUnit unit;
    double epoch_to_construct_nanos;
    double stopwatch_start_time;
    double stopwatch_stop_time;
    bool _running;
    bool _reset;
public:
    StopWatch();
    StopWatch(TimeUnit);
    void setUnit(TimeUnit);
    void start();
    void reset();
    bool running();
    double read();
    double read(TimeUnit);
    double stop();
    double stop(TimeUnit);
    void reset_start();
    double stop_reset();
    double stop_reset(TimeUnit);
    double stop_reset_start();
    double stop_reset_start(TimeUnit);

};
}

#endif /* f_time_h */
