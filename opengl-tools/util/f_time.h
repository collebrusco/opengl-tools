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
    double nanos();
    double micros();
    double millis();
    double seconds();
enum TimeUnit {
    SECONDS = 1000000000,
    MILLISECONDS = 1000000,
    MICROSECONDS = 1000,
    NANOSECONDS = 1
};
}

// stopwatch
void stopwatch_start();
double stopwatch_stop(ftime::TimeUnit);
double stopwatch_read(ftime::TimeUnit);


#endif /* f_time_h */
