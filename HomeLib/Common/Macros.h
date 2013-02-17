#ifndef MACROS_H
#define MACROS_H

/// Explicitly mark a type non-copyable.
#define NO_COPY(type) \
	private: \
	type(const type &); \
	const type &operator=(const type &); 

#endif // MACROS_H