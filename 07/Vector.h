#include <iostream>

template <class T>
class Allocator
{
public:
	using value_type = T;
	using pointer = T *;
	using size_type = size_t;
	using const_reference = const T &;

	pointer allocate(size_type count)
	{
		pointer d_data = (pointer)(::operator new(count * sizeof(value_type)));
		return d_data;
	}

	void deallocate(pointer ptr)
	{
		::operator delete(ptr);
	}

	void destroy(pointer p)
	{
		((pointer)p)->~value_type();
	}

	void construct(pointer p, const_reference val)
	{
		new((void*)p) value_type(val);
	}

	template< class U, class... Args >
	void construct(U* p, Args&& ... args)
	{
		::new((void*)p) U(std::forward<Args>(args)...);
	}
};

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
	using value_type = T;
	using pointer = T *;
	using reference = T &;

	explicit Iterator(pointer begin) : d_ptr(begin)
	{
	}

	bool operator==(const Iterator& other) const
	{
		return d_ptr == other.d_ptr;
	}

	bool operator!=(const Iterator& other) const
	{
		return !(*this == other);
	}

	Iterator& operator++()
	{
		++d_ptr;
		return *this;
	}

	Iterator& operator--()
	{
		--d_ptr;
		return *this;
	}

	reference operator*() const
	{
		return *d_ptr;
	}

	reference operator[](const int& uk)
	{
		return d_ptr[uk];
	}

private:
	pointer d_ptr;
};

template <class T>
class reverse_iterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
	using value_type = T;
	using pointer = T *;
	using reference = T &;

	explicit reverse_iterator(pointer begin) : d_ptr(begin)
	{
	}

	bool operator==(const reverse_iterator& other) const
	{
		return d_ptr == other.d_ptr;
	}

	bool operator!=(const reverse_iterator& other) const
	{
		return !(*this == other);
	}

	reverse_iterator& operator++()
	{
		--d_ptr;
		return *this;
	}

	reverse_iterator& operator--()
	{
		++d_ptr;
		return *this;
	}

	reference operator*() const
	{
		return *d_ptr;
	}

	reference operator[](const int& uk)
	{
		return d_ptr[uk];
	}

private:
	pointer d_ptr;
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
	using size_type = size_t;
	using value_type = T;
	using pointer = T *;
	using reference = T &;
	using const_reference = const T &;
	using allocator_type = Alloc;
	using iterator = Iterator<T>;
	using Reverse_iterator = reverse_iterator<T>;

	explicit Vector(size_type count = 100)
	{
		d_begin = d_alloc.allocate(count);
		d_end = d_begin;
		d_vec = d_begin + count;
	}

	~Vector()
	{
		for (pointer it = d_begin; it != d_end; ++it)
		{
			d_alloc.destroy(it);
		}
		d_alloc.deallocate(d_begin);
	}

	reference operator[](size_type pos)
	{
		return d_begin[pos];
	}

	iterator begin() noexcept
	{
		return iterator(d_begin);
	}
	Reverse_iterator rbegin() noexcept
	{
		return Reverse_iterator(d_end - 1);
	}

	iterator end() noexcept
	{
		return iterator(d_end);
	}
	Reverse_iterator rend() noexcept
	{
		return Reverse_iterator(d_begin - 1);
	}

	void push_back(value_type&& value)
	{
		if (d_end == d_vec)
		{
			reserve((d_vec - d_begin) * 2);
		}

		d_alloc.construct(d_end, std::move(value));
		++d_end;
	}

	void push_back(const value_type& value)
	{
		if (d_end == d_vec)
		{
			reserve((d_vec - d_begin) * 2);
		}
		d_alloc.construct(d_end, value);
		++d_end;
	}

	void pop_back()
	{
		if (d_begin != d_end)
		{
			--d_end;
			d_alloc.destroy(d_end);
		}
	}

	bool empty() const
	{
		return d_begin == d_end;
	}

	size_type size() const noexcept
	{
		return d_end - d_begin;
	}

	void reserve(size_type count)
	{
		if (d_vec - d_begin < count)
		{
			pointer new_buf = d_alloc.allocate(count);

			for (int i = 0; i != d_end - d_begin; ++i)
			{
				d_alloc.construct(new_buf + i, d_begin[i]);
				d_alloc.destroy(d_begin + i);
			}

			d_end = new_buf + (d_end - d_begin);
			d_alloc.deallocate(d_begin);
			d_begin = new_buf;
			d_vec = new_buf + count;
		}
	}

	size_type capacity() const noexcept
	{
		return d_vec - d_begin;
	}

	void resize(size_type newSize)
	{
		if (d_vec - d_begin < newSize)
		{
			reserve(newSize);
		}

		if (d_end - d_begin > newSize)
		{
			while (d_end != d_begin + newSize)
			{
				pop_back();
			}
		}

		if (d_end - d_begin < newSize)
		{
			while (d_end != d_begin + newSize)
			{
				d_alloc.construct(d_end, value_type());
				++d_end;
			}
		}
	}

	void clear() noexcept
	{
		while (d_end != d_begin)
		{
			d_alloc.destroy(d_end);
			--d_end;
		}
	}

private:
	Alloc d_alloc;
	pointer d_vec;
	pointer d_begin;
	pointer d_end;
};
