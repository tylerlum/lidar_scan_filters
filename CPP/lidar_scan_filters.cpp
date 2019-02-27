#include "lidar_scan_filters.h"
#include <algorithm>
#include <vector>

using namespace std;

RangeFilter::RangeFilter(double range_min, double range_max) : range_min(range_min), range_max(range_max) {}

vector<double> RangeFilter::update(vector<double> lidar_scan) {
  vector<double> filtered_lidar_scan(lidar_scan);

  // Crop data out of desired range
  for (int i = 0; i < filtered_lidar_scan.size(); i++) {
    if (filtered_lidar_scan.at(i) < range_min) { filtered_lidar_scan[i] = range_min; }
    else if (filtered_lidar_scan.at(i) > range_max) { filtered_lidar_scan[i] = range_max; }
  }

  return filtered_lidar_scan;
}

TemporalMedianFilter::TemporalMedianFilter(int D) : D(D) {}

vector<double> TemporalMedianFilter::update(vector<double> lidar_scan) {
  vector<double> new_lidar_scan(lidar_scan);

  // Remove oldest scan, if appropriate
  if (lidar_scans.size() > D) {
    lidar_scans.erase(lidar_scans.begin());
  }
  
  // Store scan
  lidar_scans.push_back(new_lidar_scan);

  vector<double> filtered_lidar_scan;
  for (int i = 0; i < lidar_scan.size(); i++) {
    // Create vector of scan data at index i
    vector<double> temp;
    for (int j = 0; j < lidar_scans.size(); j++) {
      temp.push_back(lidar_scans.at(j).at(i));
    }

    // Compute and store median
    sort(temp.begin(), temp.end());
    filtered_lidar_scan.push_back(median(temp));
  }
  return filtered_lidar_scan;
}

double TemporalMedianFilter::median(const vector<double> & v) {
  if (v.size() % 2 == 0) {
    return 0.5 * (v.at(v.size() / 2 - 1) + v.at(v.size() / 2));
  } else {
    return v.at(v.size() / 2);
  }
}
