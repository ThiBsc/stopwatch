#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>

/**
* Stopwatch C++ implementation
*/
class Stopwatch
{
public:

    typedef std::chrono::steady_clock watch;
    typedef std::chrono::steady_clock::time_point timepoint;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::seconds secs;
    typedef std::chrono::minutes mins;
    typedef std::chrono::hours hrs;

    Stopwatch();
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    /**
     * Start or restart the stopwatch
     */
    void start();
    /**
     * Start countdown
     */
    void start(ms countdown);
    /**
     * Stop the stopwatch
     */
    void stop();
    /**
     * Add msecs to the elapsed time
     */
    void addMsecs(ms msecs);
    /**
     * Return the elapsed time in ms
     */
    ms elapsed() const;
    /**
     * Return a string human readable representation
     * of the elapsed time in a specified format:
     * https://en.cppreference.com/w/cpp/io/manip/put_time
     */
    std::string elapsed(const char* fmt, bool milliseconds) const;
    /**
     * Return the remaining time in ms
     * (Use it when you start with countdown)
     */
    ms remaining() const;
    /**
     * Return a string human readable representation
     * of the remaining time in a specified format:
     * https://en.cppreference.com/w/cpp/io/manip/put_time
     */
    std::string remaining(const char* fmt, bool milliseconds) const;

private:
    watch clock;
    timepoint begin, end;
    ms countdown;
    bool isRunning;

};

#endif // STOPWATCH_H