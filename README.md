# lidar_scan_filters

__Author__: Tyler Lum

Implement two filter objects for filtering lidar scan data, in both C++ and Python2.7

## RangeFilter

A `RangeFilter` class that filters lidar scan data based on a minimum and maximum range

### Attributes
`range_min` : float
    minimum range value
    all values less than range_min will be cropped to range_min.

`range_max` : float
    maximum range value
    all values greater than range_max will be cropped to range_max.
    
## TemporalMedianFilter

A `TemporalMedianFilter` class that filters lidar scan data based on a median of previous scans

### Attributes
`D` : int
    number of previous scans to look at for median calculation (must be a non-negative integer) 
    finds median of current and previous D scans (total of D+1 scans)
    
`lidar_scans` : list
    list of previous lidar scans to perform median calculation

## Unit Tests

Unit tested these two filters with the Google Test Framework in C++ and unittest in Python. 

### C++

To run the unit tests in C++, run the following command from the `lidar_scan_filters/CPP` directory:

```
cmake CMakeLists.txt && make && ./runTests
``` 

Please ensure you have `Google Test` and `CMake` set up on your computer before running.

### Python2.7

To run the unit tests in Python2.7, run the following command from the `lidar_scan_filters/Python2.7` directory:

```
python2.7 test_lidar_scan_filters.py
``` 

Please ensure you have `unittest` set up on your computer before running.


