#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

#include "Allocator.h"
#include "../Containers/IntrusiveList.h"
#include "../Common/Macros.h"

namespace Memory
{
	struct PoolBlock_t
	{
		IntrusiveLink next;

		// Array of PoolBlob_t's here
	};

	struct PoolObject_t
	{
		IntrusiveLink next;

		// Object memory here
	};

	typedef IntrusiveList<PoolBlock_t, offsetof(PoolBlock_t, next)> BlockList;
	typedef IntrusiveList<PoolObject_t, offsetof(PoolObject_t, next)> NodeList;

	class PoolAllocator : public Allocator
	{
		NO_COPY(PoolAllocator)

	public:
		PoolAllocator(size_t blobSize);
		~PoolAllocator();

		virtual Blob_t Allocate(size_t size);
		virtual void Destroy(Blob_t blob);

	private:
		void AddBlock(size_t objectCount);

		static const size_t initialCount = 32;
		const size_t _objectSize;
		size_t _objectCount;

		BlockList _blocks;
		NodeList _freeObjects;
		NodeList _usedObjects;
	};
}

#endif // POOLALLOCATOR_H