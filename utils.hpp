#ifndef UTILS_HPP
# define UTILS_HPP

# include <memory>
# include <exception>
# include <stdexcept> 
# include <stack>
# include <algorithm>
# include <iterator>
# include <iostream>
# include <chrono>
# include <iomanip>
# include <ctime>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>

/*fonts color*/
# define FBLACK		"\033[0;30m"
# define FRED		"\033[0;31m"
# define FGREEN		"\033[0;32m"
# define FYELLOW	"\033[0;33m"
# define FBLUE		 "\033[0;34m"
# define FPURPLE	"\033[0;35m"
# define FCYAN		"\x1b[36m"

/*end color*/
# define NONE        "\033[0m"

#define WRONG_SIZE_CAP	"Wrong size or capacity!"
#define SIZE_CAP_OK		"Size and capacity are ok"

#define	SIZE_CAP_HEADER	"Size and capacity"

#define NO_RETURN_VALUE		0
#define OK_RETURN_VALUE		1
#define BAD_RETURN_VALUE	2

#define ZERO_TIME	"N/A - ft_time or std_time == 0"

// using std::chrono::high_resolution_clock;
// using std::chrono::duration_cast;
// using std::chrono::duration;
// using std::chrono::milliseconds;

# define	SIZE	10

namespace ft {

/*---------------------- Base class that provides some member types ----------------------*/
template<
	class Category,
	class T,
	class Distance = std::ptrdiff_t,
	class Pointer = T*,
	class Reference = T&> 
	struct iterator {
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

/*------------------------- enable_if -------------------------*/
template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

/*------------------------- is_iterator -------------------------*/
template<class T>
struct is_iterator {
private:
	template<class C>
	static typename C::iterator_category f(int a) {
		(void)a;
		return C::iterator_category();
	}
	template <class C>
	static double f(...) {return 0;};
public:	
	static const bool value = sizeof(f<T>(1)) != sizeof(double);
};

/* Pair is a class template that provides a way to store 
** two heterogeneous objects as a single unit */
template<class T1, class T2> 
struct pair
{
    /* Member types */
    typedef T1  first_type;
    typedef T2  second_type;

    /* Member objects */
    T1  first;
    T2  second;

    /* Member functions */
    pair() : first(T1()), second(T2()) {}
    pair( const T1& x, const T2& y ) : first(x), second(y) {}
    template< class U1, class U2 >
    pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}

    pair& operator=( const pair& other ) {
    	if (this != &other)
        {
            first = other.first;
            second = other.second;
        }
        return (*this);
    }
};

/* Creates a pair object, deducing the target type from the types of arguments. */
template< class T1, class T2 >
pair<T1,T2> make_pair( T1 t, T2 u ) { return ft::pair<T1,T2>(t, u);}

template< class T1, class T2 >
bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {return (lhs.first == rhs.first && lhs.second == rhs.second);}

template< class T1, class T2 >
bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {return !(lhs == rhs);}

template< class T1, class T2 >
bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
	if (lhs.first < lhs.first)
		return true;
	if (lhs.first > lhs.first)
		return false;
	return (lhs.second < lhs.second);
}

template< class T1, class T2 >
bool operator<=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs ) {return (lhs.first < rhs.first || lhs.first == lhs.first);}

template< class T1, class T2 >
bool operator>( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs ) {return !(lhs <= rhs);}

template< class T1, class T2 >
bool operator>=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs ) {return !(lhs < rhs);}

// https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2,
                             Compare comp)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (comp(*first1, *first2)) return true;
        if (comp(*first2, *first1)) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

}

#endif