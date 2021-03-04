#include "gtest/gtest.h"
#include "../include/AugmentedPriorityQueue.h"
#include "../include/GridStateSpace.h"

TEST(AugmentedPriorityQueueTest, testPushPop) {
	GridStateSpace ss1(0, 0);
	GridStateSpace ss2(1, 0);
	GridStateSpace ss3(3, 0);
	AugmentedPriorityQueue<GridStateSpace> q;
	AugmentedPriorityQueue<GridStateSpace>::Container item1 = std::make_tuple(ss1, 1, 0);
	AugmentedPriorityQueue<GridStateSpace>::Container item2 = std::make_tuple(ss2, 2, 2);
	AugmentedPriorityQueue<GridStateSpace>::Container item3 = std::make_tuple(ss3, 2, 3);
	ASSERT_EQ(q.Size(), 0);
	q.Push(item1);
	ASSERT_EQ(q.Size(), 1);
	q.Push(item2);
	ASSERT_EQ(q.Size(), 2);
	q.Push(item3);
	ASSERT_EQ(q.Size(), 3);
	auto getItem1 = q.Top();
	q.Pop();
	auto getItem2 = q.Top();
	q.Pop();
	auto getItem3 = q.Top();
	q.Pop();
	ASSERT_TRUE(std::get<0>(getItem1) == ss1);
	ASSERT_TRUE(std::get<0>(getItem2) == ss2);
	ASSERT_TRUE(std::get<0>(getItem3) == ss3);
}

TEST(AugmentedPriorityQueueTest, testUpdate) {
	GridStateSpace ss1(0, 0);
	GridStateSpace ss2(1, 0);
	GridStateSpace ss3(3, 0);

	AugmentedPriorityQueue<GridStateSpace> q;
	q.Emplace(ss1, 1, 0);
	q.Emplace(ss2, 2, 0);
	q.Emplace(ss3, 3, 0);

	ASSERT_TRUE(std::get<0>(q.Top()) == ss1);
	ASSERT_EQ(q.Size(), 3);

	q.Update(ss1, 0, 0);
	ASSERT_TRUE(std::get<0>(q.Top()) == ss1);
	ASSERT_EQ(q.Size(), 3);

	q.Update(ss1, 4, 0);
	ASSERT_TRUE(std::get<0>(q.Top()) == ss2);
	ASSERT_EQ(q.Size(), 3);

	q.Update(ss3, 1, 0);
	ASSERT_TRUE(std::get<0>(q.Top()) == ss3);
	ASSERT_EQ(q.Size(), 3);
}

TEST(AugmentedPriorityQueueTest, testDelete) {
	GridStateSpace ss1(0, 0);
	GridStateSpace ss2(1, 0);
	GridStateSpace ss3(3, 0);
	GridStateSpace ss4(4, 0);
	GridStateSpace ss5(5, 0);
	GridStateSpace ss6(6, 0);

	AugmentedPriorityQueue<GridStateSpace> q;

	q.Emplace(ss1, 1, 0);
	q.Emplace(ss2, 2, 0);
	q.Emplace(ss3, 3, 0);
	q.Emplace(ss4, 4, 0);
	q.Emplace(ss5, 5, 0);
	q.Emplace(ss6, 6, 0);

	ASSERT_TRUE(std::get<0>(q.Top()) == ss1);
	ASSERT_EQ(q.Size(), 6);

	ASSERT_TRUE(q.Contains(ss3));
	q.Delete(ss3);
	ASSERT_FALSE(q.Contains(ss3));

	ASSERT_TRUE(std::get<0>(q.Top()) == ss1);
	ASSERT_EQ(q.Size(), 5);

	ASSERT_TRUE(q.Contains(ss1));
	q.Delete(ss1);
	ASSERT_FALSE(q.Contains(ss1));

	ASSERT_TRUE(std::get<0>(q.Top()) == ss2);
	ASSERT_EQ(q.Size(), 4);

	ASSERT_TRUE(q.Contains(ss2));
	q.Delete(ss2);
	ASSERT_FALSE(q.Contains(ss2));

	ASSERT_TRUE(std::get<0>(q.Top()) == ss4);
	ASSERT_EQ(q.Size(), 3);

	q.Pop();
	q.Pop();
	q.Pop();
	ASSERT_EQ(q.Size(), 0);
	ASSERT_TRUE(q.Empty());
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}