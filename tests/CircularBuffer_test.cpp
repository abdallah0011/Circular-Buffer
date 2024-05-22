#include "CircularBuffer.h"
#include <gtest/gtest.h>
#include <vector>

class CircularBuffer_test :public ::testing::Test{
    void SetUp() override{
    }

    void TearDown() override{
    }
};

TEST_F(CircularBuffer_test, TEST_PUSH_BACK_CHECK_HEAD){
    CircularBuffer<int, 5> buffer;
    buffer.push_back(1);
    EXPECT_EQ(buffer.head(), 1);
    EXPECT_EQ(buffer.tail(), 0);
    buffer.push_back(2);
    EXPECT_EQ(buffer.curSize(), 2);
    EXPECT_FALSE(buffer.isEmpty());
}

TEST_F(CircularBuffer_test, TEST_PUSH_BACK_CHECK_OVERLAP_HEAD_TAIL){
    CircularBuffer<int, 5> buffer;
    for(int i = 0; i <=5; i++){
        // buffer [5,1,2,3,4]
        buffer.push_back(i);
    }
    EXPECT_EQ(buffer.head(), 1);
    EXPECT_EQ(buffer.tail(), 1);
    // EXPECT_EQ(buffer.curSize(), 5);
}


TEST_F(CircularBuffer_test, TEST_PUSH_BACK_CHECK_OVERLAP_HEAD){
    CircularBuffer<int, 5> buffer;
    for(int i = 0; i <=10; i++){
        // buffer [10,6,7,8,9]
        buffer.push_back(i);
    }
    EXPECT_EQ(buffer.head(), 6);
    // EXPECT_EQ(buffer.tail(), 6);
    // EXPECT_EQ(buffer.curSize(), 5);
}

TEST_F(CircularBuffer_test, TEST_PUSH_BACK_CHECK_POP_BACK){
    CircularBuffer<int, 5> buffer;
    std::vector<int> test {6, 7, 8, 9, 10};
    std::vector<int> result;
    for(int i = 0; i <=10; i++){
        // buffer [10,6,7,8,9]
        buffer.push_back(i);
    }

    while(!buffer.isEmpty()){
        result.push_back(buffer.head());
        buffer.pop();
    }
    EXPECT_EQ(result, test);
    EXPECT_EQ(buffer.curSize(), 0); // gurantee our buffer is clear
    EXPECT_EQ(buffer.head(), buffer.tail());
    EXPECT_THROW(buffer.pop(), std::runtime_error); // an empty buffer throws error when popping
}

TEST_F(CircularBuffer_test, TEST_PUSH_BACK_CHECK_INITIALIZER_LIST){
    CircularBuffer<int, 5> buffer{6, 7, 8, 9, 10};
    std::vector<int> test {6, 7, 8, 9, 10};
    std::vector<int> result;
    EXPECT_EQ(buffer.curSize(), test.size());

    while(!buffer.isEmpty()){
        result.push_back(buffer.head());
        buffer.pop();
    }
    EXPECT_EQ(result, test);
    EXPECT_EQ(buffer.curSize(), 0);
}

TEST_F(CircularBuffer_test, TEST_PUSH_BACK_CHECK_INITIALIZER_LIST_THROW){
    try{
        CircularBuffer<int, 5> buffer{6, 7, 8, 9, 10, 5, 1, 2, 4};
        FAIL();
    }catch (std::runtime_error e){
        EXPECT_TRUE(true);
    }
}

TEST_F(CircularBuffer_test, TEST_ITERATOR){
    CircularBuffer<int, 5> buffer{1, 2, 3, 4, 5};
    int sum1 = 15, sum2 = 14;
    int res1 = 0;
    int res2 = 0;
    std::for_each(buffer.begin(), buffer.end(), [&res1](auto &a){
        res1 += a;
    });
    
    std::for_each(++buffer.begin(), buffer.end(), [&res2](auto &a){
        res2 += a;
    });

    EXPECT_EQ(res1, sum1);
    EXPECT_EQ(res2, sum2);
}

TEST_F(CircularBuffer_test, TEST_ITERATOR_VALUES){
    CircularBuffer<int, 5> buffer{1, 2, 3, 4, 5};
    std::cout << buffer.beginn() << '\n';
    std::cout << buffer.endd() << '\n';
}