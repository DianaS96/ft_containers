#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utils.hpp"
# include "random_access_iterator.hpp"
#include <type_traits>
/* SOURCES OF INFO:
** 1) https://www.youtube.com/watch?v=_wE7JYfcKN0
** 2) https://en.cppreference.com/w/cpp/container/vector
** 3) https://cplusplus.com/reference/vector/vector/?kw=vector
*/

namespace ft {

template <
    class T,
    class Allocator = std::allocator<T>
> class vector
{
	public:
	/*-------------------- MEMBER TYPES --------------------*/
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef typename allocator_type::pointer		pointer;
		typedef typename allocator_type::const_pointer	const_pointer;

		typedef class ft::random_access_iterator<T>				iterator;
		typedef class ft::random_access_iterator<const T>		const_iterator;
		typedef class ft::rev_random_access_iterator<T>			reverse_iterator;
		typedef class ft::rev_random_access_iterator<const T>	const_reverse_iterator;

	/*-------------------- MEMBER FUNCTIONS --------------------*/
		/* Default constructor. Constructs an empty container with a default-constructed allocator. */
		vector();
		/* Constructs an empty container with the given allocator alloc. */
		explicit vector( const Allocator& alloc );
		/*  Constructs the container with count copies of elements with value value. */
		explicit vector( size_type count,
					const T& value,
					const Allocator& alloc = Allocator());
		/* Constructs the container with the contents of the range [first, last). */
		template < class InputIt >
		vector( typename ft::enable_if<ft::is_iterator<InputIt>::value, InputIt>::type first, 
				InputIt last, const Allocator& alloc = Allocator() );
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
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;

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
		// void resize( size_type count );
		void resize( size_type count, T value );
		/* Exchanges the contents of the container with those of other. */
		void swap( vector& other );

	private:
		size_type	_capacity;
		size_type	_size;
		Allocator	_alloc;
		T*			_array;
	/*-------------------- NON-MEMBER FUNCTIONS --------------------*/

};

template <class T, class Allocator>
vector<T, Allocator>::vector() : _capacity(0), _size(0), _alloc(allocator_type()), _array(NULL) {}

template <class T, class Allocator>
vector<T, Allocator>::vector( const Allocator& alloc ) : _capacity(0), _size(0), _alloc(alloc), _array(NULL) {}

template <class T, class Allocator>
vector<T, Allocator>::vector(size_type count,
							const T& value, 
							const Allocator& alloc) : 
							_capacity(count), 
							_size(count),
							_alloc(alloc) {
	_array = _alloc.allocate(_capacity);
	size_type i = 0;
	try {
		for (; i < _size; ++i)
			_alloc.construct(_array + i, value);
	}
	catch(...)
	{
		for (size_t j = 0; j < i; ++j)
			_alloc.destroy(_array + j);
		_alloc.deallocate(_array, _capacity);
		throw;
	}
}

template <class T, class Allocator>
template < class InputIt >
vector<T, Allocator>::vector( typename ft::enable_if<ft::is_iterator<InputIt>::value, InputIt>::type first, 
							InputIt last, const Allocator& alloc ) : 
							_capacity(0), _size(0), _alloc(alloc), _array(NULL) {
	size_type	i;
	InputIt		tmp(first);

	_size = 0;
	while (*tmp != *last)
	{
		tmp++;
		_size++;
	}
	_capacity = _size;
	_array = _alloc.allocate(_capacity);
	try {
		for (i = 0; *first != *last; ++i, first++)
			_alloc.construct(_array + i, *first);
	}
	catch(...)
	{
		for (size_type j = 0; j < i; ++j)
			_alloc.destroy(_array + j);
		_alloc.deallocate(_array, _capacity);
		throw;
	}
}
				
template <class T, class Allocator>
vector<T, Allocator>::	vector( const vector& other ) : _capacity(other._capacity), 
														_size(other._size), 
														_alloc(other._alloc) {
	_array = _alloc.allocate(_capacity);
	size_type i = 0;
	try {
		for (; i < _size; ++i)
			_alloc.construct(_array + i, other._array[i]);
	}
	catch(...)
	{
		for (size_type j = 0; j < i; ++j)
			_alloc.destroy(_array + j);
		_alloc.deallocate(_array, _capacity);
		throw;
	}
}

template <class T, class Allocator>
vector<T, Allocator>::~vector() {
	for (size_type i = 0; i < _size; ++i)
		_alloc.destroy(_array + i);
	_alloc.deallocate(_array, _capacity);
}

template <class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=( const vector& other ) {
	if (this == &other)
		return (*this);

	T *newarr = _alloc.allocate(other._capacity);
	size_type i = 0;
	try {
		for (; i < other._size; ++i)
			_alloc.construct(newarr + i, other._array[i]);
	}
	catch(...)
	{
		for (size_type j = 0; j < i; ++j)
			_alloc.destroy(newarr + i);
		_alloc.deallocate(newarr, other._capacity);
		throw;
	}
	
	for (size_type i = 0; i < _size; ++i)
		_alloc.destroy(_array + i);
	_alloc.deallocate(_array, _capacity);
	
	_array = newarr;
	_capacity = other._capacity;
	_size = other._size;
	return (*this);
}

// template <class T, class Allocator>
// void vector<T, Allocator>::assign( size_type count, const T& value ) {
// 	size_type	i = 0;
// 	if (count > _capacity)
// 	{
// 		for (; i < _size; ++i)
// 			_alloc.destroy(_array + i);
// 		_alloc.deallocate(_array, _capacity);
// 	}
// }


/*----------------------------------------  Element access ----------------------------------------*/
template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at( size_type pos ) {
	if (pos >= _size)
		throw std::out_of_range("invalid vector subscript");
	return (_array[pos]);
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at( size_type pos ) const {
	if (pos >= _size)
		throw std::out_of_range("invalid vector subscript");
	return (_array[pos]);
}

template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::operator[]( size_type pos ) {
	return (_array[pos]);
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[]( size_type pos ) const {
	return (_array[pos]);
}

template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::front() {
	return (_array[0]);
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const {
	return (_array[0]);
}

template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::back() {
	return (_array[_size - 1]);
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const {
	return (_array[_size - 1]);
}

template <class T, class Allocator>
T* vector<T, Allocator>::data() {
	return (_array);
}

template <class T, class Allocator>
const T* vector<T, Allocator>::data() const {
	return (_array);
}


/*---------------------------------------- Capacity ----------------------------------------*/
template <class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const {
	return (_size);
}

template <class T, class Allocator>
void vector<T, Allocator>::reserve( size_type new_cap ) {
	if (new_cap <= _capacity)
		return ;
	T *newarr = _alloc.allocate(new_cap);
	size_t i = 0;
	try {
		for (; i < _size; ++i)
			_alloc.construct(newarr + i, _array[i]);
	}
	catch(...)
	{
		for (size_t j = 0; j < i; ++j)
			_alloc.destroy(newarr + i);
		_alloc.deallocate(newarr, new_cap);
		throw;
	}
	
	for (size_t i = 0; i < _size; ++i)
		_alloc.destroy(_array + i);
	_alloc.deallocate(_array, _capacity);
	_array = newarr;
	_capacity = new_cap;
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const {
	return (_capacity);
}


/*---------------------------------------- Modifiers ----------------------------------------*/

template <class T, class Allocator>
void vector<T, Allocator>::clear() {
	for (size_type i = 0; i < _size; ++i)
		_alloc.destroy(_array + i);
	_size = 0;
}

// iterator insert( iterator pos, const T& value );
// void insert( iterator pos, size_type count, const T& value );
// template < class InputIt >
// void insert( iterator pos, InputIt first, InputIt last );
// iterator erase( iterator pos );
// iterator erase( iterator first, iterator last );

template <class T, class Allocator>
void vector<T, Allocator>::push_back( const T& value ) {
	if (_capacity == 0)
	{
		_alloc.deallocate(_array, _capacity);
		_array = _alloc.allocate(1);
		_capacity = 1;
	}
	else if (_size == _capacity)
	{
		T *newarr = _alloc.allocate(_capacity * 2);
		size_t i = 0;
		try {
			for (; i < _size; ++i)
				_alloc.construct(newarr + i, _array[i]);
		}
		catch(...)
		{
			for (size_t j = 0; j < i; ++j)
				_alloc.destroy(newarr + i);
			_alloc.deallocate(newarr, _capacity * 2);
			throw;
		}
		for (size_t j = 0; j < _size; ++j)
				_alloc.destroy(_array + i);
			_alloc.deallocate(_array, _capacity);
		_array = newarr;
		_capacity = _capacity * 2;
	}
	_alloc.construct(_array + _size, value);
	++_size;
}

template <class T, class Allocator>
void vector<T, Allocator>::pop_back() {
	--_size;
	(_array + _size)->~T();
}

template <class T, class Allocator>
void vector<T, Allocator>::resize( size_type count, T value ) {
	size_type i;

	if (count < _size)
	{
		for (i = count; i < _size; ++i)
			_alloc.destoy(_array + i);
	}
	else
	{
		i = _size;
		try {
			for (; i < count; ++i)
				push_back(value);
		}
		catch(...)
		{
			for (; i > size; --i)
				_alloc.destroy(_array + i);
			throw;
		}
	}
	_size = count;
}

template <class T, class Allocator>
void vector<T, Allocator>::swap( vector& other ) {
	std::swap(_size, other._size);
	std::swap(_capacity, other._capacity);
	std::swap(_array, other._array);
}	

/*---------------------------------------- Iterators ----------------------------------------*/
template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() {
	return iterator(_array);
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::end() {
	return iterator(_array + _size);
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const {
	return const_iterator(_array);
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const {
	return const_iterator(_array + _size);
}

template <class T, class Allocator>
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin() {
	return reverse_iterator(this->end());
}

template <class T, class Allocator>
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend() {
	return reverse_iterator(this->begin());
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const {
	return v(this->end());
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const {
	return const_reverse_iterator(this->begin());
}


		// reverse_iterator end();
		// const_reverse_iterator begin();
		// const_reverse_iterator end();

}

#endif