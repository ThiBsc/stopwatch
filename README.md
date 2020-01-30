# stopwatch
[![Build Status](https://travis-ci.org/ThiBsc/stopwatch.svg?branch=master)](https://travis-ci.org/ThiBsc/stopwatch) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)  
A command line stopwatch  
<code style="font-family: courier; color: #fff; background: #881798">00:00:07.235</code>

## Compile
```bash
make
# Install
mv ./bin/sw /usr/bin
```

## Use
Foreground and background [color](https://en.wikipedia.org/wiki/ANSI_escape_code#Colors)  
```bash
# Start a stopwatch
sw
# Start a countdown (hh:mm:ss)
sw -c 00:00:30
# Execute cmd after the countdown
sw -c 00:00:30 && cmd

# On unix system, you can change the display color
./sw --fg 97 --bg 45
```

## C++ Sample

```cpp
Stopwatch sw;
sw.start();

// do something

cout << sw.elapsed_HHMMSSZZZ() << endl;
```
