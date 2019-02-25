import unittest
import numpy as np

from lidar_scan_filters import RangeFilter
from lidar_scan_filters import TemporalMedianFilter

class TestRangeFilter(unittest.TestCase):

    def test_1(self):
        rf = RangeFilter(1, 10)
        scan1 = np.array([1,2,3,4,5])
        self.assertTrue((rf.update(scan1) == scan1).all())

        scan2 = np.array([12, 10, 3, 9, 2])
        self.assertTrue((rf.update(scan2) == np.array([10, 10, 3, 9, 2])).all())

        scan3 = np.array([12, 10, 0.05, 9.2, 0.2])
        self.assertTrue((rf.update(scan3) == np.array([10, 10, 1, 9.2, 1])).all())

    def test_2(self):
        rf = RangeFilter(0.3, 100)
        scan1 = np.array([1,2,3,4,5])
        self.assertTrue((rf.update(scan1) == scan1).all())

        scan2 = np.array([12, 10, 3, 9, 2])
        self.assertTrue((rf.update(scan2) == scan2).all())

        scan3 = np.array([12, 10, 0.05, 9.2, 0.2])
        self.assertTrue((rf.update(scan3) == np.array([12, 10, 0.3, 9.2, 0.3])).all())


class TestTemporalMedianFilter(unittest.TestCase):
    def test_odd_D(self):
        tmf = TemporalMedianFilter(3)
        scan1 = np.array([1,2,3,4,5])
        self.assertTrue((tmf.update(scan1) == scan1).all())

        scan2 = np.array([5,4,3,2,1])
        self.assertTrue((tmf.update(scan2) == np.array([3, 3, 3, 3, 3])).all())

        scan3 = np.array([2,2,2,2,2])
        self.assertTrue((tmf.update(scan3) == np.array([2, 2, 3, 2, 2])).all())

        scan4 = np.array([1.5,2.5,3.5,4.5,5.5])
        self.assertTrue((tmf.update(scan4) == np.array([1.75, 2.25, 3, 3, 3.5])).all())

        scan5 = np.array([10,20,30,40,50])
        self.assertTrue((tmf.update(scan5) == np.array([3.5, 3.25, 3.25, 3.25, 3.75])).all())

    def test_even_D(self):
        tmf = TemporalMedianFilter(2)
        scan1 = np.array([1,2,3,4,5])
        self.assertTrue((tmf.update(scan1) == scan1).all())

        scan2 = np.array([5,4,3,2,1])
        self.assertTrue((tmf.update(scan2) == np.array([3, 3, 3, 3, 3])).all())

        scan3 = np.array([2,2,2,2,2])
        self.assertTrue((tmf.update(scan3) == np.array([2, 2, 3, 2, 2])).all())

        scan4 = np.array([1.5,2.5,3.5,4.5,5.5])
        self.assertTrue((tmf.update(scan4) == np.array([2, 2.5, 3, 2, 2])).all())

        scan5 = np.array([10,20,30,40,50])
        self.assertTrue((tmf.update(scan5) == np.array([2, 2.5, 3.5, 4.5, 5.5])).all())


if __name__ == "__main__":
    unittest.main()

