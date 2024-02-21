#include "alloc.h"

Allocator::~Allocator() { delete[] memBegin; }

void Allocator::makeAllocator(size_t maxSize) {
	if (memBegin != nullptr) delete[] memBegin;
	fullSize = maxSize;
	memBegin = new char[maxSize];
	offset = 0;
}

char* Allocator::alloc(size_t size) {
	if (offset + size > fullSize) {
		return nullptr;
	}
	offset += size;
	return memBegin + offset - size;
}

void Allocator::reset() {
	offset = 0;
}
