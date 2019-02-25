#ifndef LIDAR_SCAN_FILTERS_H_
#define LIDAR_SCAN_FILTERS_H_

#include <vector>

class RangeFilter {
public:

  RangeFilter(double range_min, double range_max);

  std::vector<double> update(std::vector<double> lidar_scan);

private:
  double range_min;
  double range_max;

};

class TemporalMedianFilter {
public:
  TemporalMedianFilter(int D);

  std::vector<double> update(std::vector<double> lidar_scan);
private:
  int D;
  std::vector< std::vector<double> > lidar_scans;

};
#endif
