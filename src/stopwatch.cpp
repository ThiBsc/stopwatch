#include "header/stopwatch.h"

#include <cassert>

// Use (void) to silent unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

Stopwatch::Stopwatch()
{
    assertm(std::chrono::steady_clock::is_steady, "You can't use steady_clock");
}

void Stopwatch::start()
{
    begin = clock.now();
}

void Stopwatch::start(ms countdown)
{
    this->countdown = countdown;
    begin = clock.now();
}

Stopwatch::ms Stopwatch::elapsed() const
{
    return std::chrono::duration_cast<Stopwatch::ms>(clock.now() - begin);
}

std::string Stopwatch::elapsed_HHMMSSZZZ() const
{
    Stopwatch::ms ms = elapsed();

    Stopwatch::ms mmm = ms % 1000;
    Stopwatch::secs ss = std::chrono::duration_cast<Stopwatch::secs>(ms) % 60;
    Stopwatch::mins mm = std::chrono::duration_cast<Stopwatch::mins>(ms) % 60;
    Stopwatch::hrs hh = std::chrono::duration_cast<Stopwatch::hrs>(ms);

    std::stringstream sstream;
    sstream << std::setfill('0') << std::setw(2) << hh.count()
    << ':' << std::setfill('0') << std::setw(2) << mm.count()
    << ':' << std::setfill('0') << std::setw(2) << ss.count()
    << '.' << std::setfill('0') << std::setw(3) << mmm.count();
    return sstream.str();
}

Stopwatch::ms Stopwatch::remaining() const
{
    Stopwatch::ms millisec = std::chrono::duration_cast<Stopwatch::ms>(countdown - (clock.now() - begin));
    return (millisec < Stopwatch::ms(0) ? Stopwatch::ms(0) : millisec);
}

std::string Stopwatch::remaining_HHMMSSZZZ() const
{
    Stopwatch::ms ms = remaining();

    Stopwatch::ms mmm = ms % 1000;
    Stopwatch::secs ss = std::chrono::duration_cast<Stopwatch::secs>(ms) % 60;
    Stopwatch::mins mm = std::chrono::duration_cast<Stopwatch::mins>(ms) % 60;
    Stopwatch::hrs hh = std::chrono::duration_cast<Stopwatch::hrs>(ms);

    std::stringstream sstream;
    sstream << std::setfill('0') << std::setw(2) << hh.count()
    << ':' << std::setfill('0') << std::setw(2) << mm.count()
    << ':' << std::setfill('0') << std::setw(2) << ss.count()
    << '.' << std::setfill('0') << std::setw(3) << mmm.count();
    return sstream.str();
}
