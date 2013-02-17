#ifndef INTRUSIVELIST_H
#define INTRUSIVELIST_H

#include <cstdint>
#include <cassert>
#include <iterator>

class IntrusiveLink;

template<class T, size_t offset>
class IntrusiveList
{
public:

	template<typename ref_type, typename ptr_type>
    class iterator_impl
    {
    public:
        typedef iterator_impl             self_type;
        typedef T                         value_type;
        typedef ref_type                  reference;
        typedef ptr_type                  pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef ptrdiff_t                 difference_type;

        iterator_impl(IntrusiveLink *ptr) : _ptr(ptr)
        {
        }

        reference operator*()
        {
            return *get();
        }

        pointer operator->()
        {
            return get();
        }

        bool operator==(const self_type& rhs)
        {
            return _ptr == rhs._ptr;
        }

        bool operator!=(const self_type& rhs)
        {
            return _ptr != rhs._ptr;
        }

        self_type operator++()
        {
            self_type i = *this;
            _ptr = _ptr ? _ptr->_next : nullptr;
            return i;
        }

        self_type operator++(int)
        {
            _ptr = _ptr ? _ptr->_next : nullptr;
            return *this;
        }

    private:

        T *get() const
        {
            uint8_t *link_ptr = reinterpret_cast<uint8_t*>(_ptr);
            return reinterpret_cast<T*>(link_ptr - offset);
        }

        IntrusiveLink *_ptr;
    };

	typedef size_t                                        size_type;
	typedef T&                                            reference;
    typedef T*                                            pointer;
    typedef iterator_impl<reference, pointer>             iterator;
    typedef iterator_impl<const reference, const pointer> const_iterator;

    IntrusiveList() :
        _head(nullptr),
        _tail(nullptr),
        _size(0)
    {
    }

    ~IntrusiveList()
    {
        clear();
    }

    size_type size() const
    { return _size; }

    bool empty() const
    {
        return _size == 0;
    }

    reference front()
    {
        assert(!empty());
        return *begin();
    }

    reference back()
    {
        assert(!empty());
        return *end();
    }

    iterator begin()
    {
        return iterator(_head);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

    const_iterator cbegin()
    {
        return const_iterator(_head);
    }

    const_iterator cend()
    {
        return const_iterator(nullptr);
    }

    void insert(const_iterator i, reference value)
    {
        IntrusiveLink *link = get(&value);
        IntrusiveLink *next = get(i.operator ->());

        assert(link);
        assert(link->_next == nullptr);
        assert(link->_prev == nullptr);

        /* Empty */
        if(_head == nullptr && _tail == nullptr)
        {
            _head = link;
            _tail = link;
        }

        /* Insert after tail */
        else if(next == nullptr)
        {
            link->_prev = _tail;
            _tail->_next = link;

            _tail = link;
        }

        /* Insert as first element */
        else if(next == _head)
        {
            link->_next = _head;
            _head->_prev = link;
            _head = link;
        }

        /* Insert in middle of list */
        else
        {
            IntrusiveLink *prev = next->_prev;

            link->_prev = prev;
            prev->_next = link;

            link->_next = next;
            next->_prev = link;
        }

        _size++;
    }

    void push_front(reference value)
    {
        insert(cbegin(), value);
    }

    void push_back(reference value)
    {
        insert(cend(), value);
    }

    void erase(const_iterator i)
    {
        IntrusiveLink *next;
        IntrusiveLink *prev;
        IntrusiveLink *link = get(i.operator ->());

        next = link ? link->_next : nullptr;
        prev = link ? link->_prev : nullptr;

        assert(link);
        link->_next = nullptr;
        link->_prev = nullptr;

		// Fix head/tail pointers
		if(link == _head) _head = next;
		if(link == _tail) _tail = prev;
		
		// Fix prev/next pointers
		if(next) next->_prev = prev;
		if(prev) prev->_next = next;

        _size--;
    }

    void erase(reference value)
    {
        erase(const_iterator(get(&value)));
    }

    void pop_back()
    {
        assert(!empty());
        erase(const_iterator(_tail));
    }

    void pop_front()
    {
        assert(!empty());
        erase(cbegin());
    }

    void clear()
    {
        while(!empty()) pop_front();
    }

private:
    static IntrusiveLink *get(T *t)
    {
        uint8_t *t_addr = reinterpret_cast<uint8_t*>(t);
        return reinterpret_cast<IntrusiveLink*>(t_addr + offset);
    }

    IntrusiveLink *_head;
    IntrusiveLink *_tail;
    size_type _size;
};

class IntrusiveLink
{
public:
    IntrusiveLink() : _next(nullptr), _prev(nullptr)
    {
    }

    IntrusiveLink *_next;
    IntrusiveLink *_prev;
};

#endif // INTRUSIVELIST_H
