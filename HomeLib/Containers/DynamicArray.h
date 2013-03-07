#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <cassert>

#include "../Memory/Allocator.h"
#include "../Common/Macros.h"

namespace Container
{
	template<class T>
	class DynamicArray
	{
		NO_COPY(DynamicArray);

	public:
		DynamicArray(size_t length);
		DynamicArray(size_t length, Memory::Allocator *allocator);
		DynamicArray(Memory::Blob_t blob);
		~DynamicArray();

		size_t length() const;
		T &operator[](size_t index);
		const T &operator[](size_t index) const;

	private:
		void init();
		void deinit();

		T* _ptr;
		size_t _length;
		Memory::Blob_t _blob;
	};
}

template<class T>
Container::DynamicArray<T>::DynamicArray(size_t length)
{
	_length = length;
	_blob = Memory::GlobalAllocate(sizeof(T) * length);
	_ptr = reinterpret_cast<T*>(_blob.ptr);
	init();
}

template<class T>
Container::DynamicArray<T>::DynamicArray(size_t length, Memory::Allocator *allocator)
{
	_length = length;
	_blob = allocator->Allocate(sizeof(T) * length);
	_ptr = reinterpret_cast<T*>(_blob.ptr);
	init();
}

template<class T>
Container::DynamicArray<T>::DynamicArray(Memory::Blob_t blob)
{
	_length = blob.size / sizeof(T);
	_blob = blob;
	_ptr = reinterpret_cast<T*>(_blob.ptr);
	init();
}

template<class T>
Container::DynamicArray<T>::~DynamicArray()
{
	deinit();
	_blob.allocator->Free(_blob);
}

template<class T>
size_t Container::DynamicArray<T>::length() const
{
	return _length;
}

template<class T>
T &Container::DynamicArray<T>::operator[](size_t index)
{
	assert(index < _length);
	return*(_ptr + index);
}

template<class T>
const T &Container::DynamicArray<T>::operator[](size_t index) const
{
	assert(index < _length);
	return*(_ptr + index);
}

template<class T>
void Container::DynamicArray<T>::init()
{
	for(size_t i = 0; i < _length; i++)
	{
		T* element = _ptr + i;
		new(element) T();
	}
}

template<class T>
void Container::DynamicArray<T>::deinit()
{
	for(size_t i = 0; i < _length; i++)
	{
		T* element = _ptr + i;
		element->~T();
	}
}

#endif // DYNAMICARRAY_H