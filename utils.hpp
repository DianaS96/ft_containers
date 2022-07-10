#ifndef UTILS_HPP
# define UTILS_HPP

# include <iterator>
namespace ft {

/*---------------------- Base class that provides some member types ----------------------*/
template<
	class Category,
	class T,
	class Distance = std::ptrdiff_t,
	class Pointer = T*,
	class Reference = T&
> struct iterator {
	typedef	Category    iterator_category;
	typedef	T           value_type;
	/* Distance - Type that can be used to identify distance between iterators. */
	typedef	Distance	difference_type;
	typedef Pointer		pointer;
	typedef	Reference	reference;
};

/*-------------------------------- Iterator category tags --------------------------------*/
struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator_tag { };
struct contiguous_iterator_tag: public random_access_iterator_tag { };

/*------------------------------------ Iterator traits -----------------------------------*/
template< class Iter >
struct iterator_traits {
	typedef	typename Iter::difference_type		difference_type;
	typedef typename Iter::value_type			value_type;
	typedef	typename Iter::pointer				pointer;
	typedef typename Iter::reference			reference;
	typedef typename Iter::iterator_category	iterator_category;
};

template< class T >
struct iterator_traits<T*> {
	typedef	std::ptrdiff_t				difference_type;
	typedef T							value_type;
	typedef	T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template< class T >
struct iterator_traits<const T*> {
	typedef	std::ptrdiff_t				difference_type;
	typedef T							value_type;
	typedef	const T*					pointer;
	typedef const T&					reference;
	typedef random_access_iterator_tag	iterator_category;
};

}

#endif