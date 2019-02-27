#ifndef LIDAR_SCAN_FILTERS_H_
#define LIDAR_SCAN_FILTERS_H_

#include <vector>

using namespace std;

class RangeFilter {
public:

  /**
   * Initialize RangeFilter.
   *
   * @param range_min minimum range value
   * @param range_max maximum range value
   */
  RangeFilter(double range_min, double range_max);

  /**
   * Filter lidar_scan using a range filter
   * All values in lidar_scan less than range_min will be changed to range_min
   * All values in lidar_scan greater than range_max will be changed to range_max
   *
   * @param lidar_scan vector<double> containing lidar range data
   * @return vector<double> with the same length as lidar_scan, which has been range filtered
   */
  vector<double> update(vector<double> lidar_scan);

private:
  double range_min;
  double range_max;
};

class TemporalMedianFilter {
public:

  /**
   * Initialize TemporalMedianFilter object
   * @param D number of previous scans to look at for median calculation (must be a non-negative integer)
   */
  TemporalMedianFilter(int D);

  /**
   * Filter lidar_scan using a temporal median filter
   * Each element in the returned vector<double> is the median of the current and previous D scans
   * For the first D scans, this will return the median of all the scans so far
   * y_i(t) = median(x_i(t) + x_i(t-1) + x_i(t-2) ... + x_i(t-D))
   *
   * @param lidar_scan vector<double> containing lidar range data
   * @return vector<double> with the same length as lidar_scan after passing through a temporal median filter
   */
  vector<double> update(vector<double> lidar_scan);

private:

  /**
   * Compute median of vector
   */
  double median(const vector<double> & v);
  int D;
  vector< vector<double> > lidar_scans;

};
#endif
