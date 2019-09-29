// Copyright 2019 Plotnikov Aleksey <alex280201@gmail.com>

#include <gtest/gtest.h>
#include <header.hpp>

TEST(SharedPtr, init) {
  SharedPtr<int> sp1;
  EXPECT_EQ(sp1, false);

  int* a = new int(13);
  SharedPtr<int> sp2(a);

  EXPECT_EQ(sp2, true);
  EXPECT_EQ(*sp2, 13);
  EXPECT_EQ(sp2.use_count(), 1);

  SharedPtr<int> sp3(sp2);

  EXPECT_EQ(sp3, true);
  EXPECT_EQ(*sp2, *sp3);
  EXPECT_EQ(sp2.use_count(), 2);
  EXPECT_EQ(sp3.use_count(), 2);
  EXPECT_EQ(sp2.get(), sp3.get());
}

TEST(SharedPtr, assign) {
  int* a = new int(28);
  SharedPtr<int> sp1(a);
  auto sp2 = sp1;

  EXPECT_EQ(*sp2, 28);
  EXPECT_EQ(sp1.use_count(), 2);
  EXPECT_EQ(sp1.use_count(), sp2.use_count());

  int* b = new int(0);
  SharedPtr<int> sp3(b);

  EXPECT_EQ(sp3.use_count(), 1);

  sp1 = sp3;

  EXPECT_EQ(sp3.use_count(), 2);
  EXPECT_EQ(*sp1, 0);
}

TEST(SharedPtr, reset_swap) {
  int* a = new int(2);
  SharedPtr<int> sp1(a);

  EXPECT_EQ(sp1.use_count(), 1);

  sp1.reset();

  EXPECT_EQ(sp1.use_count(), 0);
  EXPECT_THROW(*sp1, std::invalid_argument);

  a = new int(2);
  SharedPtr<int> sp2(a);
  int* b = new int(2001);
  sp1 = sp2;

  EXPECT_EQ(sp2.use_count(), 2);
  EXPECT_EQ(*sp2, 2);

  sp2.reset(b);

  EXPECT_EQ(sp2.use_count(), 1);
  EXPECT_EQ(*sp2, 2001);
  EXPECT_EQ(sp1.use_count(), 1);
  EXPECT_EQ(*sp1, 2);

  SharedPtr<int> sp3(sp2);

  EXPECT_EQ(sp3.use_count(), 2);
  EXPECT_EQ(*sp3, 2001);
  EXPECT_EQ(sp1.use_count(), 1);
  EXPECT_EQ(*sp1, 2);

  sp3.swap(sp1);

  EXPECT_EQ(sp3.use_count(), 1);
  EXPECT_EQ(*sp3, 2);
  EXPECT_EQ(sp1.use_count(), 2);
  EXPECT_EQ(*sp1, 2001);
}
