#include "Allocator.h"

#include <cstdlib>

namespace Memory
{
	class GlobalAllocator : public Allocator
	{
	public:
		virtual Blob_t Allocate(size_t size)
		{
			Blob_t result;
			result.size = size;
			result.ptr = reinterpret_cast<uint8_t*>(std::malloc(size));
			result.allocator = this;
			return result;
		}

		virtual void Free(Blob_t blob)
		{
			std::free(blob.ptr);
			blob.ptr = nullptr;
			blob.size = 0;
		}
	};

	static GlobalAllocator globalAllocator;
}


Memory::Blob_t Memory::GlobalAllocate(size_t size)
{
	return globalAllocator.Allocate(size);
}

void Memory::GlobalFree(Blob_t &blob)
{
	globalAllocator.Free(blob);
}
