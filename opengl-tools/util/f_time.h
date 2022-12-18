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
void stopwatch_start();                 // start stopwatch
double stopwatch_stop(ftime::TimeUnit); // stop & read stopwatch
double stopwatch_read(ftime::TimeUnit); // read stopwatch, safe even after stop
}

#endif /* f_time_h */
