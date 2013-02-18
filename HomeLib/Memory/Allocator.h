#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstdint>

namespace Memory
{

	/// A region of memory.
	struct Blob_t
	{
		size_t size;
		uint8_t *ptr;

		Blob_t() : size(0), ptr(nullptr) {}
	};

	/// Global blob allocation function.
	Blob_t Allocate(size_t size);

	/// Global blob free function.
	void Free(Blob_t &blob);

	/// An allocator interface.
	class Allocator
	{
	public:

		/// Try to allocate a region of memory of size. Check the
		/// return value to see how much memory was actually allocated.
		virtual Blob_t Allocate(size_t size) = 0;
		
		/// Free a previously allocated region of memory.
		virtual void Free(Blob_t blob) = 0;
	};
}

#endif // ALLOCATOR_H