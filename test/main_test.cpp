#include <iostream>
#include <string>
#include "gtest/gtest.h"
int Foo(int a, int b){
    if (a == 0 || b == 0)
    {
        throw "don't do that";
    }
    int c = a % b;
    if (c == 0)
        return b;
    return Foo(b, c);
}

TEST(FooTest, HandleNoneZeroInput){
    EXPECT_EQ(2, Foo(4, 10));
    EXPECT_EQ(6, Foo(30, 18));
}

int _tmain(int argc, _TCHAR* argv[]){
    	testing::InitGoogleTest(&argc, argv);
    	return RUN_ALL_TESTS();
}