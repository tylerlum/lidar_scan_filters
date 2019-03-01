#include "lidar_scan_filters.cpp"
#include <gtest/gtest.h>
#include <vector>
#include <boost/assign/list_of.hpp>

/**
 * Check that all elements of vector<double> are double equal
 */
void checkDoubleVectorsEqual(const std::vector<double> & v1, const std::vector<double> & v2) {
  EXPECT_EQ(v1.size(), v2.size());

  for (int i = 0; i < v1.size(); i++) {
    EXPECT_DOUBLE_EQ(v1.at(i), v2.at(i));
  }
}

TEST(RangeFilterTest, SmallRange) {
  RangeFilter r(1, 10);

  std::vector<double> scan1 = boost::assign::list_of<double>(1)(2)(3)(4)(5);
  std::vector<double> expected1 = scan1; 
  checkDoubleVectorsEqual(r.update(scan1), expected1);

  std::vector<double> scan2 = boost::assign::list_of<double>(12)(20)(3)(9)(2);
  std::vector<double> expected2 = boost::assign::list_of<double>(10)(10)(3)(9)(2);
  checkDoubleVectorsEqual(r.update(scan2), expected2);

  std::vector<double> scan3 = boost::assign::list_of<double>(13)(10)(0.05)(9.2)(0.2);
  std::vector<double> expected3 = boost::assign::list_of<double>(10)(10)(1)(9.2)(1);
  checkDoubleVectorsEqual(r.update(scan3), expected3);
}

TEST(RangeFilterTest, LargeRange) {
  RangeFilter r(0.3, 100);

  std::vector<double> scan1 = boost::assign::list_of<double>(1)(2)(3)(4)(5);
  std::vector<double> expected1 = scan1; 
  checkDoubleVectorsEqual(r.update(scan1), expected1);

  std::vector<double> scan2 = boost::assign::list_of<double>(12)(200)(3)(99.5)(100.5);
  std::vector<double> expected2 = boost::assign::list_of<double>(12)(100)(3)(99.5)(100);
  checkDoubleVectorsEqual(r.update(scan2), expected2);

  std::vector<double> scan3 = boost::assign::list_of<double>(130)(10)(0.05)(999.2)(0.02);
  std::vector<double> expected3 = boost::assign::list_of<double>(100)(10)(0.3)(100)(0.3);
  checkDoubleVectorsEqual(r.update(scan3), expected3);
}

TEST(TemporalMedianFilterTest, oddD) {
  TemporalMedianFilter t(3);

  std::vector<double> scan1 = boost::assign::list_of<double>(1)(2)(3)(4)(5);
  std::vector<double> expected1 = scan1;
  checkDoubleVectorsEqual(t.update(scan1), expected1);

  std::vector<double> scan2 = boost::assign::list_of<double>(5)(4)(3)(2)(1);
  std::vector<double> expected2 = boost::assign::list_of<double>(3)(3)(3)(3)(3);
  checkDoubleVectorsEqual(t.update(scan2), expected2);

  std::vector<double> scan3 = boost::assign::list_of<double>(2)(2)(2)(2)(2);
  std::vector<double> expected3 = boost::assign::list_of<double>(2)(2)(3)(2)(2);
  checkDoubleVectorsEqual(t.update(scan3), expected3);

  std::vector<double> scan4 = boost::assign::list_of<double>(1.5)(2.5)(3.5)(4.5)(5.5);
  std::vector<double> expected4 = boost::assign::list_of<double>(1.75)(2.25)(3)(3)(3.5);
  checkDoubleVectorsEqual(t.update(scan4), expected4);
  
  std::vector<double> scan5 = boost::assign::list_of<double>(10)(20)(30)(40)(50);
  std::vector<double> expected5 = boost::assign::list_of<double>(3.5)(3.25)(3.25)(3.25)(3.75);
  checkDoubleVectorsEqual(t.update(scan5), expected5);
}

TEST(TemporalMedianFilterTest, evenD) {
  TemporalMedianFilter t(2);

  std::vector<double> scan1 = boost::assign::list_of<double>(1)(2)(3)(4)(5);
  std::vector<double> expected1 = scan1;
  checkDoubleVectorsEqual(t.update(scan1), expected1);

  std::vector<double> scan2 = boost::assign::list_of<double>(5)(4)(3)(2)(1);
  std::vector<double> expected2 = boost::assign::list_of<double>(3)(3)(3)(3)(3);
  checkDoubleVectorsEqual(t.update(scan2), expected2);

  std::vector<double> scan3 = boost::assign::list_of<double>(2)(2)(2)(2)(2);
  std::vector<double> expected3 = boost::assign::list_of<double>(2)(2)(3)(2)(2);
  checkDoubleVectorsEqual(t.update(scan3), expected3);

  std::vector<double> scan4 = boost::assign::list_of<double>(1.5)(2.5)(3.5)(4.5)(5.5);
  std::vector<double> expected4 = boost::assign::list_of<double>(2)(2.5)(3)(2)(2);
  checkDoubleVectorsEqual(t.update(scan4), expected4);
  
  std::vector<double> scan5 = boost::assign::list_of<double>(10)(20)(30)(40)(50);
  std::vector<double> expected5 = boost::assign::list_of<double>(2)(2.5)(3.5)(4.5)(5.5);
  checkDoubleVectorsEqual(t.update(scan5), expected5);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
