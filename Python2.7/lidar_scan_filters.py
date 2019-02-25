import numpy as np
import sys, os

class RangeFilter:
    """
    A RangeFilter class that filters lidar scan data based on a minimum and maximum range

    ...

    Attributes
    ----------
    range_min : float
        minimum range value
        all values less than range_min will be cropped to range_min.
    range_max : float
        maximum range value
        all values greater than range_max will be cropped to range_max.

    """
    
    def __init__(self, range_min, range_max):
        """
        Initialize RangeFilter object
        
        Args:
            range_min: minimum range value, all values less than range_min will be cropped to range_min.
            range_max: maximum range value, all values greater than range_max will be cropped to range_max.

        """
        # Store member variables
        self.range_min = range_min
        self.range_max = range_max

    def update(self, lidar_scan):
        """
        Filter lidar_scan using a range filter
        
        Args:
            lidar_scan: numpy array of lidar range data
            
        Returns:
            a numpy array with the same length as lidar_scan, which has been range filtered
            all values in lidar_scan less than range_min will be changed to range_min
            all values in lidar_scan greater than range_max will be changed to range_max            

        """
        # Make copy to ensure no changes made to input 
        filtered_lidar_scan = np.copy(lidar_scan)

        # Perform range filtering
        filtered_lidar_scan[filtered_lidar_scan < self.range_min] = self.range_min
        filtered_lidar_scan[filtered_lidar_scan > self.range_max] = self.range_max
        return filtered_lidar_scan

class TemporalMedianFilter:
    """
    A TemporalMedianFilter class that filters lidar scan data based on a median of previous scans
    ...

    Attributes
    ----------
    D : int
        number of previous scans to look at for median calculation (must be a non-negative integer) 
        finds median of current and previous D scans (total of D+1 scans)
    lidar_scans : list
        list of previous lidar scans to perform median calculation

    """
    
    def __init__(self, D):
        """
        Initialize TemporalMedianFilter object
        
        Args:
            D: number of previous scans to look at for median calculation (must be a non-negative integer) 

        """
        # Initialize member variables
        self.D = D
        self.lidar_scans = []

    def update(self, lidar_scan):
        """
        Filter lidar_scan using a temporal median filter
        
        Args:
            lidar_scan: numpy array of lidar range data
            
        Returns:
            a numpy array with the same length as lidar_scan, after passing through a temporal median filter
            each element in the returned numpy array is the median of the current and previous D scans
            for the first D scans, this will return the median of all the scans so far
            y_i(t) = median(x_i(t) + x_i(t-1) + x_i(t-2) ... + x_i(t-D))

        """
        # Remove stale scans
        if (len(self.lidar_scans) > self.D):
            self.lidar_scans = self.lidar_scans[-self.D:]
            
        # Add new lidar scans and compute median
        self.lidar_scans.append(np.copy(lidar_scan))
        np_lidar_scans = np.array(self.lidar_scans)
        return np.median(np_lidar_scans, axis=0)


if __name__ == "__main__":
    # Parameters
    range_min = 5
    range_max = 20
    D = 3
    N = 5

    data_min = 0.03
    data_spread = 49.97

    # Create filter objects
    rf = RangeFilter(range_min, range_max)
    tmf = TemporalMedianFilter(D)

    # Test lidar data
    ls1 = np.random.rand(N) * data_spread + data_min
    ls2 = np.random.rand(N) * data_spread + data_min
    ls3 = np.random.rand(N) * data_spread + data_min
    ls4 = np.random.rand(N) * data_spread + data_min
    ls5 = np.random.rand(N) * data_spread + data_min
    ls6 = np.random.rand(N) * data_spread + data_min
    ls7 = np.random.rand(N) * data_spread + data_min
    ls8 = np.random.rand(N) * data_spread + data_min

    # Show lidar data
    print("Lidar data")
    print((ls1))
    print((ls2))
    print((ls3))
    print((ls4))
    print((ls5))
    print((ls6))

    print("************************\n")

    # Test RangeFilter
    print("Range Filtered Lidar data")
    print(rf.update(ls1))
    print(rf.update(ls2))
    print(rf.update(ls3))
    print(rf.update(ls4))
    print(rf.update(ls5))
    print(rf.update(ls6))
    
    print("************************\n")

    # Test Temporal Median Filter
    print("Temporal Median Filtered Lidar data")
    print(tmf.update(ls1))
    print(tmf.update(ls2))
    print(tmf.update(ls3))
    print(tmf.update(ls4))
    print(tmf.update(ls5))
    print(tmf.update(ls6))
    
    print("************************\n")

    # Show lidar data does not get affected
    print("Lidar data")
    print((ls1))
    print((ls2))
    print((ls3))
    print((ls4))
    print((ls5))
    print((ls6))

