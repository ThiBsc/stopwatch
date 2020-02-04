#include "header/stopwatch.h"

#include <cassert>

// Use (void) to silent unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

Stopwatch::Stopwatch()
    : isRunning(false)
{
    assertm(std::chrono::steady_clock::is_steady, "You can't use steady_clock");
}

void Stopwatch::start()
{
    begin = clock.now();
    isRunning = true;
}

void Stopwatch::start(ms countdown)
{
    this->countdown = countdown;
    begin = clock.now();
    isRunning = true;
}

void Stopwatch::stop()
{
    if (isRunning){
        end = clock.now();
        isRunning = false;
    }
}

void Stopwatch::addMsecs(ms msecs)
{
    begin -= msecs;
}

Stopwatch::ms Stopwatch::elapsed() const
{
    return std::chrono::duration_cast<Stopwatch::ms>( (isRunning ? clock.now() : end) - begin);
}

std::string Stopwatch::elapsed(const char* fmt, bool milliseconds) const
{
    Stopwatch::ms ms = elapsed();

    Stopwatch::ms zzz = ms % 1000;
    Stopwatch::secs ss = std::chrono::duration_cast<Stopwatch::secs>(ms) % 60;
    Stopwatch::mins mm = std::chrono::duration_cast<Stopwatch::mins>(ms) % 60;
    Stopwatch::hrs hh = std::chrono::duration_cast<Stopwatch::hrs>(ms);

    // https://en.cppreference.com/w/cpp/chrono/c/tm
    std::tm tm = { int(ss.count()), int(mm.count()), int(hh.count()), 0, 0, 0, 0, 0, 0 };

    std::stringstream sstream;
    sstream << std::put_time(&tm, fmt);
    if (milliseconds){
        sstream << '.' << std::setfill('0') << std::setw(3) << zzz.count();
    }

    return sstream.str();
}

Stopwatch::ms Stopwatch::remaining() const
{
    Stopwatch::ms millisec = countdown - elapsed();
    return (millisec < Stopwatch::ms(0) ? Stopwatch::ms(0) : millisec);
}

std::string Stopwatch::remaining(const char* fmt, bool milliseconds) const
{
    Stopwatch::ms ms = remaining();

    Stopwatch::ms zzz = ms % 1000;
    Stopwatch::secs ss = std::chrono::duration_cast<Stopwatch::secs>(ms) % 60;
    Stopwatch::mins mm = std::chrono::duration_cast<Stopwatch::mins>(ms) % 60;
    Stopwatch::hrs hh = std::chrono::duration_cast<Stopwatch::hrs>(ms);

    // https://en.cppreference.com/w/cpp/chrono/c/tm
    std::tm tm = { int(ss.count()), int(mm.count()), int(hh.count()), 0, 0, 0, 0, 0, 0 };

    std::stringstream sstream;
    sstream << std::put_time(&tm, fmt);
    if (milliseconds){
        sstream << '.' << std::setfill('0') << std::setw(3) << zzz.count();
    }
    
    return sstream.str();
}
