#include <gtest/gtest.h>
#include "multiset.h"

TEST(Multiset, Empty) {
  Multiset<int> mset;

  /* Should be fully empty */
  EXPECT_EQ(mset.Empty(), true);
  EXPECT_EQ(mset.Size(), 0);
  EXPECT_THROW(mset.Count(42), std::exception);
}

TEST(Multiset, OneKey) {
  Multiset<int> mset;

  /* Test some insertion */
  mset.Insert(23);
  mset.Insert(42);
  mset.Insert(42);
  EXPECT_EQ(mset.Empty(), false);
  EXPECT_EQ(mset.Size(), 3);
  EXPECT_EQ(mset.Min(), 23);
  EXPECT_EQ(mset.Max(), 42);
  EXPECT_EQ(mset.Count(42), 2);
}

TEST(Multiset, CeilFloor) {
  Multiset<int> mset;

  /* Test functionality of the Ceiling, Floor, and Contains functions*/
  mset.Insert(23);
  mset.Insert(21);
  mset.Insert(43);
  mset.Insert(45);
  EXPECT_EQ(mset.Empty(), false);
  EXPECT_EQ(mset.Size(), 4);
  EXPECT_EQ(mset.Ceil(44), 45);
  EXPECT_EQ(mset.Ceil(45), 45);
  EXPECT_EQ(mset.Floor(30), 23);
  EXPECT_EQ(mset.Floor(23), 23);
  EXPECT_EQ(mset.Contains(23), true);
}

TEST(Multiset, Error) {
  Multiset<int> mset;

  /* Should be fully empty */
  EXPECT_THROW(mset.Remove(3), std::exception);
  EXPECT_THROW(mset.Floor(3), std::exception);
  EXPECT_THROW(mset.Ceil(3), std::exception);
  EXPECT_THROW(mset.Max(), std::exception);
  EXPECT_THROW(mset.Min(), std::exception);

  /* Test out of range errors */
  mset.Insert(100);
  EXPECT_THROW(mset.Floor(4), std::exception);
  EXPECT_THROW(mset.Ceil(101), std::exception);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

