#include "Allocator.h"

#include <cstdlib>

Memory::Blob_t Memory::Allocate(size_t size)
{
	Blob_t result;
	result.size = size;
	result.ptr = reinterpret_cast<uint8_t*>(std::malloc(size));
	return result;
}

void Memory::Free(Blob_t &blob)
{
	std::free(blob.ptr);
	blob.ptr = nullptr;
	blob.size = 0;
}
