#ifndef ARRAY_H
#define ARRAY_H

#include <cstdint>
#include <cassert>

#include "../Common/Macros.h"

namespace Container
{

	// A dynamic 2d array.
	template<class T>
	class Array2D
	{
		NO_COPY(Array2D)

	public:

		// Construct a 2d array with the given width and height.
		inline Array2D(size_t width, size_t height);

		// Dtor.
		inline ~Array2D(void);

		// Return the number of columns.
		inline size_t width() const;

		// Return the number of rows.
		inline size_t height() const;
		
		// Return a pointer to the data store.
		inline T** data();

		// Return a const pointer to the data store.
		inline const T** data() const;

		// Return a reference to the element at the location. Bounds checked.
		inline T& at(size_t x, size_t y);

		// Return a const reference to the element at the location. Bounds checked.
		inline const T& at(size_t x, size_t y) const;

		// Return a pointer to the y'th row.
		inline T* operator[](size_t y);

		// Return a const pointer to the y'th row.
		inline const T* operator[](size_t y) const;

	private:
		const size_t _width;
		const size_t _height;
		T** _array;
	};
}

template<class T>
Container::Array2D<T>::Array2D(size_t width, size_t height) :
	_width(width),
	_height(height)
{
	assert(width > 0);
	assert(height > 0);

	_array = new T*[sizeof(T*) * _height];

	T* elements = new T[width * height];
	for(size_t y = 0; y < _height; y++)
	{
		_array[y] = &elements[y * _width]; 
	}
}

template<class T>
Container::Array2D<T>::~Array2D(void)
{
	delete [] _array[0];
	delete [] _array;
}

template<class T>
size_t Container::Array2D<T>::width() const
{
	return _width;
}

template<class T>
size_t Container::Array2D<T>::height() const
{
	return _height;
}

template<class T>
T** Container::Array2D<T>::data()
{
	return _data;
}

template<class T>
const T** Container::Array2D<T>::data() const
{
	return _data;
}

template<class T>
T& Container::Array2D<T>::at(size_t x, size_t y)
{
	assert((x >= 0) && (x < width()));
	assert((y >= 0) && (y < height()));
	return (*this)[y][x];
}

template<class T>
const T& Container::Array2D<T>::at(size_t x, size_t y) const
{
	assert((x >= 0) && (x < width()));
	assert((y >= 0) && (y < height()));
	return (*this)[y][x];
}

template<class T>
T* Container::Array2D<T>::operator[](size_t y)
{
	return _array[y];
}

template<class T>
const T* Container::Array2D<T>::operator[](size_t y) const
{
	return _array[y];
}

#endif // ARRAY_H