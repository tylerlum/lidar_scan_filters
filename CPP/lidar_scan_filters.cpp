#include "lidar_scan_filters.h"
#include <algorithm>
#include <iostream>
#include <vector>

RangeFilter::RangeFilter(double range_min, double range_max) : range_min(range_min), range_max(range_max) {}

std::vector<double> RangeFilter::update(std::vector<double> lidar_scan) {
  std::vector<double> filtered_lidar_scan(lidar_scan);
  //std::replace_if(filtered_lidar_scan.begin(), filtered_lidar_scan.end(), RangeFilter::belowMin, range_min);
  //std::replace_if(filtered_lidar_scan.begin(), filtered_lidar_scan.end(), RangeFilter::aboveMax, range_max);

  for (int i = 0; i < filtered_lidar_scan.size(); i++) {
    if (filtered_lidar_scan.at(i) < range_min) { filtered_lidar_scan[i] = range_min; }
    else if (filtered_lidar_scan.at(i) > range_max) { filtered_lidar_scan[i] = range_max; }
  }

  return filtered_lidar_scan;
}


TemporalMedianFilter::TemporalMedianFilter(int D) : D(D) {}

std::vector<double> TemporalMedianFilter::update(std::vector<double> lidar_scan) {
  std::vector<double> new_lidar_scan(lidar_scan);
  if (lidar_scans.size() > D) {
    lidar_scans.erase(lidar_scans.begin()); // may adjust to always work
  }
  
  lidar_scans.push_back(new_lidar_scan);
  std::vector<double> filtered_lidar_scan;

  for (int i = 0; i < lidar_scan.size(); i++) {
    std::vector<double> temp;
    for (int j = 0; j < lidar_scans.size(); j++) {
      temp.push_back(lidar_scans.at(j).at(i));
    }
    std::sort(temp.begin(), temp.end());
    if (temp.size() % 2 == 0) {
      filtered_lidar_scan.push_back(0.5 * (temp[temp.size() / 2 - 1] + temp[temp.size() / 2]));
    } else {
      filtered_lidar_scan.push_back(temp[temp.size() / 2]);
    }
  }
  return filtered_lidar_scan;
}
