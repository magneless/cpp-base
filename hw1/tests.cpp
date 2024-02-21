#include <gtest/gtest.h>
#include "alloc.h"

TEST (AllocTest, ReturnNullptr) {
	Allocator al;
	al.makeAllocator(8);

	char* a = al.alloc(9);
	char* b = al.alloc(3);
	ASSERT_TRUE(a == nullptr);
	ASSERT_TRUE(b != nullptr);
}

TEST (AllocTest, RightShift) {
	Allocator al;
	al.makeAllocator(4);

	char* a = al.alloc(2);
	char* b = al.alloc(2);
	ASSERT_TRUE(a+2 == b);
}

TEST (AllocTest, MultiplyCalls) {
	Allocator al;
	al.makeAllocator(9);

	char* a = al.alloc(3);
	char* b = al.alloc(3);
	char* c = al.alloc(3);
	char* d = al.alloc(1);
	ASSERT_TRUE(a != nullptr);
	ASSERT_TRUE(b != nullptr);
	ASSERT_TRUE(c != nullptr);
	ASSERT_TRUE(d == nullptr);
}

TEST (ResetTest, RightReset) {
	Allocator al;
	al.makeAllocator(8);

	char* a = al.alloc(4);	
	char* b = al.alloc(4);
	ASSERT_TRUE(a != b);

	al.reset();
	b = al.alloc(4);
	ASSERT_TRUE(a == b);
}

int main(int argc, char** argv) {

	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
