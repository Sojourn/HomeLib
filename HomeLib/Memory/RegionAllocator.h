#ifndef REGIONALLOCATOR_H
#define REGIONALLOCATOR_H

#include "../Common/Macros.h"
#include "Allocator.h"

namespace Memory
{

	/// A class which allocates by subdividing an existing memory region.
	class RegionAllocator : public Allocator
	{
		NO_COPY(RegionAllocator)

	public:

		/// Construct on an existing region.
		RegionAllocator(Blob_t region);

		/// Allocate a region
		virtual Blob_t Allocate(size_t size);

		/// Pop a region off the top.
		virtual void Free(Blob_t blob);

	private:
		const Blob_t _region;
		uint8_t *_top;
	};
}

#endif // REGIONALLOCATOR_H