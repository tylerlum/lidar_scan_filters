#include "lidar_scan_filters.cpp"
#include <gtest/gtest.h>
#include <vector>

TEST(RangeFilterTest, SmallRange) {
  RangeFilter r(1, 10);
  //std::vector<double> scan1 = {1, 2, 3, 4, 5};
  std::vector<double> scan1;
  for (int i = 1; i <= 5; i++) {
    scan1.push_back(i);
  }

  EXPECT_TRUE(scan1 == r.update(scan1));

  std::vector<double> scan2;
  scan2.push_back(12);
  scan2.push_back(10);
  scan2.push_back(3);
  scan2.push_back(9);
  scan2.push_back(2);
  std::vector<double> expected2(scan2);
  expected2[0] = 10;
  EXPECT_TRUE(expected2 == r.update(scan2));

  std::vector<double> scan3;
  scan3.push_back(13);
  scan3.push_back(10);
  scan3.push_back(0.05);
  scan3.push_back(9.2);
  scan3.push_back(0.2);
  std::vector<double> expected3(scan3);
  expected3[0] = 10;
  expected3[2] = 1;
  expected3[4] = 1;
  EXPECT_TRUE(expected3 == r.update(scan3));
}

TEST(TemporalMedianFilterTest, oddD) {
  TemporalMedianFilter t(3);
  std::vector<double> scan1;
  for (int i = 1; i <= 5; i++) {
    scan1.push_back(i);
  }
  EXPECT_TRUE(scan1 == t.update(scan1));

  std::vector<double> scan2;
  for (int i = 5; i >= 1; i--) {
    scan2.push_back(i);
  }
  std::vector<double> expected2;
  for (int i = 1; i <= 5; i++) {
    expected2.push_back(3);
  }
  EXPECT_TRUE(expected2 == t.update(scan2));

  std::vector<double> scan3;
  for (int i = 1; i <= 5; i++) {
    scan3.push_back(2);
  }
  std::vector<double> expected3(scan3);
  expected3[2] = 3;
  EXPECT_TRUE(expected3 == t.update(scan3));

  std::vector<double> scan4;
  for (int i = 1; i <= 5; i++) {
    scan4.push_back(0.5 + i);
  }
  std::vector<double> expected4;
  expected4.push_back(1.75);expected4.push_back(2.25);expected4.push_back(3);expected4.push_back(3);expected4.push_back(3.5);
  EXPECT_TRUE(expected4 == t.update(scan4));
  
  std::vector<double> scan5;
  for (int i = 1; i <= 5; i++) {
    scan5.push_back(10 * i);
  }
  std::vector<double> expected5;
  expected5.push_back(3.5);expected5.push_back(3.25);expected5.push_back(3.25);expected5.push_back(3.25);expected5.push_back(3.75);
  EXPECT_TRUE(expected5 == t.update(scan5));
  
  
  
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
