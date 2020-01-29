# stopwatch
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)  
A command line stopwatch

## Compile
```bash
make
```

## Use
```bash
# Start a stopwatch
./sw
# Start a countdown (hh:mm:ss)
./sw -c 00:00:30
# Execute cmd after the countdown
./sw -c 00:00:30 && cmd
```

## C++ Sample

```cpp
Stopwatch sw;
sw.start();

// do something

cout << sw.elapsed_HHMMSSZZZ() << endl;
```
