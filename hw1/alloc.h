#pragma once
#include <cstddef>

class Allocator {
public:
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();

	~Allocator();
private:
	char* memBegin = nullptr;
	size_t fullSize = 0;
	size_t offset = 0;
};
