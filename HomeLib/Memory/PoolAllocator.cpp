#include "PoolAllocator.h"

#include <algorithm>
#include <cstring>
#include <cassert>

Memory::PoolAllocator::PoolAllocator(size_t blobSize) :
	_objectSize(blobSize)
{
	AddBlock(initialCount);
}

Memory::PoolAllocator::~PoolAllocator()
{
	while(_blocks.size() > 0)
	{
		PoolBlock_t *block = &_blocks.front();
		_blocks.pop_front();
		
		// FIXME: calculate blob size
		Blob_t blob;
		blob.ptr = reinterpret_cast<uint8_t*>(block);
		Memory::Free(blob);
	}
}

Memory::Blob_t Memory::PoolAllocator::Allocate(size_t size)
{
	assert(_objectSize >= size);

	if(_freeObjects.size() > 0)
	{
		// Move a blob from the free list to the used list
		PoolObject_t *object = &_freeObjects.back();
		_freeObjects.pop_back();
		_usedObjects.push_back(*object);

		// Return the blob
		Blob_t blob;
		blob.size = _objectSize;
		blob.ptr = reinterpret_cast<uint8_t*>(object) + sizeof(PoolObject_t);
		return blob;
	}
	else
	{
		// Add additional capacity before trying again
		AddBlock(_objectCount);
		return Allocate(size);
	}
}

void Memory::PoolAllocator::Free(Blob_t blob)
{
	// Add the blob to the free list
	PoolObject_t *object = reinterpret_cast<PoolObject_t*>(blob.ptr - sizeof(PoolObject_t));
	_usedObjects.erase(*object);
	_freeObjects.push_back(*object);
}

void Memory::PoolAllocator::AddBlock(size_t blobCount)
{
	// Allocate a new block
	size_t allocSize = 0;
	allocSize += sizeof(PoolBlock_t);
	allocSize += blobCount * (sizeof(PoolObject_t) + _objectSize);
	Blob_t blockBlob = Memory::Allocate(allocSize);
	std::memset(blockBlob.ptr, 0, blockBlob.size);

	// Register the block
	PoolBlock_t *block = reinterpret_cast<PoolBlock_t*>(blockBlob.ptr);
	_blocks.push_back(*block);

	// Get the address of a object given its index
	auto GetPoolObject = [=](size_t index) -> PoolObject_t *
	{
		uint8_t *addr = reinterpret_cast<uint8_t*>(block);
		
		size_t offset = 0;
		offset += sizeof(PoolBlock_t);
		offset += index * (sizeof(PoolObject_t) + _objectSize);
		return reinterpret_cast<PoolObject_t*>(addr + offset);
	};

	// Add the blobs to the free list
	for(size_t i = 0; i < blobCount; i++)
	{
		_freeObjects.push_back(*GetPoolObject(i));
		_objectCount++;
	}
}