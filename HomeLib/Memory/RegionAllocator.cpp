#include <cassert>

#include "RegionAllocator.h"

Memory::RegionAllocator::RegionAllocator(Blob_t region) :
	_region(region),
	_top(region.ptr)
{
}

Memory::Blob_t Memory::RegionAllocator::Allocate(size_t size)
{
	if(((_top + size) - _region.ptr) > static_cast<ptrdiff_t>(_region.size))
	{
		return Blob_t();
	}
	else
	{
		Blob_t blob;
		blob.size = size;
		blob.ptr = _top;
		_top += size;
		return blob;
	}
}

void Memory::RegionAllocator::Free(Blob_t blob)
{
	assert(blob.ptr = _top);
	_top -= blob.size;
}