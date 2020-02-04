# stopwatch
[![Build Status](https://travis-ci.org/ThiBsc/stopwatch.svg?branch=master)](https://travis-ci.org/ThiBsc/stopwatch) [![AUR-GIT](https://img.shields.io/aur/version/stopwatchcpp.svg?color=3fbaec)](https://aur.archlinux.org/packages/stopwatchcpp/) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)  
A command line stopwatch  
<code style="font-family: courier; color: #fff; background: #881798">00:00:07.235</code>

## Compile
```bash
make
# Install
mv ./bin/sw /usr/bin
# Display help
sw --help
```

## Use
Foreground and background [color](https://en.wikipedia.org/wiki/ANSI_escape_code#Colors)  
```bash
# Start a stopwatch
sw
# Start a countdown (hh:mm:ss)
sw -c 00:00:30
# Change the display format (mm:ss.zzz) / (mm:ss)
sw -f %M:%S
sw -f %M:%S -m
# Execute cmd after the countdown
sw -c 00:00:30 && cmd
# Measure the execution time of a process
ping localhost -c 3 | sw

# On unix system, you can change the display color
./sw --fg 97 --bg 45
```

## C++ Sample

```cpp
Stopwatch sw;
sw.start();

// do something

// https://en.cppreference.com/w/cpp/io/manip/put_time
cout << sw.elapsed("%H:%M:%S", true) << endl;
```
