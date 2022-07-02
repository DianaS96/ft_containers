#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <exception>
#include <stdexcept> 

/* SOURCES OF INFO:
** 1) https://www.youtube.com/watch?v=_wE7JYfcKN0
** 2) https://en.cppreference.com/w/cpp/container/vector
** 3) https://cplusplus.com/reference/vector/vector/?kw=vector
*/

template <
    class T,
    class Allocator = std::allocator<T>
> class vector
{
	public:
	/*-------------------- MEMBER TYPES --------------------*/
		typedef Т										value_type;
		typedef Allocator								allocator_type;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef typename allocator_type::pointer		pointer;
		typedef typename allocator_type::const_pointer	const_pointer;

		class	iterator;
		class	const_iterator;
		// reverse_iterator
		// const_reverse_iterator


	/*-------------------- MEMBER FUNCTIONS --------------------*/
		/* Default constructor. Constructs an empty container with a default-constructed allocator. */
		vector();
		/* Constructs an empty container with the given allocator alloc. */
		explicit vector( const Allocator& alloc );
		/*  Constructs the container with count copies of elements with value value. */
		explicit vector( size_type count,
					const T& value = T(),
					const Allocator& alloc = Allocator());
		/* Constructs the container with the contents of the range [first, last). */
		template < class InputIt >
		vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
		/* Copy constructor. Constructs the container with the copy of the contents of other. */
		vector( const vector& other );

		~vector();

		vector& operator=( const vector& other );

		/* Replaces the contents with count copies of value value */
		void assign( size_type count, const T& value );
		/* Replaces the contents with copies of those in the range [first, last). */
		template < class InputIt >
		void assign( InputIt first, InputIt last );

		/* Returns the allocator associated with the container. */
		allocator_type get_allocator() const;


		/*--------------------  Element access --------------------*/
		/* Returns a reference to the element at specified location pos, with bounds checking. */	
		reference at( size_type pos );
		const_reference at( size_type pos ) const;
		/* Returns a reference to the element at specified location pos. No bounds checking is performed. */
		reference operator[]( size_type pos );
		const_reference operator[]( size_type pos ) const;
		/* Returns a reference to the first element in the container. */
		reference front();
		const_reference front() const;
		/* Returns a reference to the last element in the container. */
		reference back();
		const_reference back() const;
		/* Returns pointer to the underlying array serving as element storage. */
		T* data();
		const T* data() const;


		/*-------------------- Iterators --------------------*/
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;


		/*-------------------- Capacity --------------------*/
		/* Checks if the container has no elements, i.e. whether begin() == end(). */
		bool empty() const;
		/* Returns the number of elements in the container, i.e. std::distance(begin(), end()). */
		size_type size() const;
		/* Returns the maximum possible number of elements */
		size_type max_size() const;
		/* Increase the capacity of the vector */
		void reserve( size_type new_cap );
		/* Returns the number of elements that the container has currently allocated space for. */
		size_type capacity() const;
		/* Requests the removal of unused capacity. */
		void shrink_to_fit();


		/*-------------------- Modifiers --------------------*/
		/* Erases all elements from the container. After this call, size() returns zero. */
		void clear();
		/* Inserts elements at the specified location in the container. */
		iterator insert( iterator pos, const T& value );
		void insert( iterator pos, size_type count, const T& value );
		template < class InputIt >
		void insert( iterator pos, InputIt first, InputIt last );
		/* Erases the specified elements from the container. */
		iterator erase( iterator pos );
		iterator erase( iterator first, iterator last );
		/* Appends the given element value to the end of the container. */
		void push_back( const T& value );
		/* Removes the last element of the container. */
		void pop_back();
		/* Resizes the container to contain count elements. */
		void resize( size_type count );
		void resize( size_type count, T value = T() );
		/* Exchanges the contents of the container with those of other. */
		void swap( vector& other );

	private:
		T*			_array;
		size_type	_capacity;
		size_type	_size;
		Allocator	_alloc;
	/*-------------------- NON-MEMBER FUNCTIONS --------------------*/

};

template <class T, class Allocator>
vector<T, Allocator>::reference vector<T, Allocator>::operator[]( size_type pos ) {
	return (_array[pos])
}

template <class T, class Allocator>
vector<T, Allocator>::const_reference vector<T, Allocator>::operator[]( size_type pos ) const {
	return (_array[pos])
}

template <class T, class Allocator>
vector<T, Allocator>::reference vector<T, Allocator>::at( size_type pos ) {
	if (pos >= _size)
		throw std::out_of_range("invalid vector subscript");
	return (_array[pos]);
}

template <class T, class Allocator>
vector<T, Allocator>::const_reference vector<T, Allocator>::at( size_type pos ) const {
	if (pos >= _size)
		throw std::out_of_range("invalid vector subscript");
	return (_array[pos]);
}

template <class T, class Allocator>
void vector<T, Allocator>::reserve( size_type new_cap ) {
	if (new_cap <= _capacity)
		return ;
	T *newarr = reinterpret_cast<T *>(new int8_t[new_cap * sizeof(T)]);
	size_t i = 0;
	try {
		for (size_t i = 0; i < _size; ++i)
			new (newarr + i) T(_array[i]);
	}
	catch(...)
	{
		for (size_t j = 0; j < i; ++j)
			(newarr	+ j)->~T();
		delete [] reinterpret_cast<int8_t>(newarr);
		throw;
	}
	
	for (size_t i = 0; i < _size; ++i)
		(_array + i)->~T();
	delete reinterpret_cast<int8_t *>(_array);
	_array = newarr;
	_capacity = new_cap;
}

template <class T, class Allocator>
void vector<T, Allocator>::resize( size_type count, T value = T() ) {
	if (count > _capacity)
		reserve (count);
	for (size_t i = _size; i < count; ++i)
		new (_array + i) T(value);
	if (count < _size)
		_size = count;
}

template <class T, class Allocator>
void vector<T, Allocator>::push_back( const T& value ) {
	if (_capacity == _size)
		reserve(2 * _size);
	new (_array + _size) T(value);
	++_size;
}

template <class T, class Allocator>
void vector<T, Allocator>::pop_back() {
	--_size;
	(_array + _size)->~T();
}

#endif