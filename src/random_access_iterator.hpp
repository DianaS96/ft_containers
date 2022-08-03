#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP
#include <iterator>

/*https://code.woboq.org/gcc/libstdc++-v3/include/bits/stl_iterator.h.html#_ZNKSt16reverse_iteratorptEv*/
# include "utils.hpp"

namespace ft {

	template <typename T>
	struct remove_const
	{
		typedef T type;
	};
	template <typename T>
	struct remove_const<const T>
	{
		typedef T type;
	};

/*--------------------------------------- random_access_iterator ---------------------------------------*/
template <typename T>
class random_access_iterator : public ft::iterator<std::random_access_iterator_tag, T>
{
public:
	typedef std::random_access_iterator_tag									iterator_category;
	typedef T																iterator_type;
	typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
	typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
	typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
	typedef typename ft::iterator_traits<iterator_type>::reference			reference;
	// typedef typename ft::iterator_traits<iterator_type>::iterator_category		iterator_category;

	random_access_iterator() : current(NULL) {}
	random_access_iterator(pointer const _x) : current(_x) {}
	template <typename T1>
	random_access_iterator(const random_access_iterator<T1>& _x) : current(_x.getPtr()) {}
	random_access_iterator &operator=(const random_access_iterator& _x) {
		if (this != &_x)
			current = _x.current;
		return (*this);
	}

	random_access_iterator &operator=(random_access_iterator<remove_const<T> >& _x) {std::cout<<"here666\n";
		current = _x.getPtr();
		return (*this);
	}

	~random_access_iterator() {}

	pointer getPtr() const {return current;}

	reference operator*() const {return (*this->current);}
	pointer operator->() const {return (&current);}
	random_access_iterator &operator++() {
		++current;
		return (*this);
	}
	random_access_iterator operator++(int) {
		random_access_iterator tmp = *this;
		++current;
		return (tmp);
	}
	random_access_iterator &operator--() {
		--current;
		return (*this);
	}
	random_access_iterator operator--(int) {
		random_access_iterator tmp = *this;
		--current;
		return (tmp);
	}

	reference operator[](difference_type n) const {return (current[n]);}
	random_access_iterator &operator+=(difference_type n) {
		current += n;
		return (*this);
		}
	random_access_iterator &operator-=(difference_type n) {
		current -= n;
		return (*this);
		}
	random_access_iterator operator+(difference_type n) {return random_access_iterator(current + n);}
	random_access_iterator operator-(difference_type n) {return random_access_iterator(current - n);}
	difference_type operator-(const random_access_iterator & rhs) {return (current - rhs.current);}

	private:
		pointer	current;
};
	template <typename T>
	bool operator==(const random_access_iterator<T>& _x, const random_access_iterator<T>& _y) {return (_x.getPtr() == _y.getPtr());}
	template <typename T>
	bool operator!=(const random_access_iterator<T>& _x, const random_access_iterator<T>& _y) {return (_x.getPtr() != _y.getPtr());}
	template <typename T>
	bool operator>(const random_access_iterator<T>& _x, const random_access_iterator<T>& _y) {return (_x.getPtr() > _y.getPtr());}
	template <typename T>
	bool operator>=(const random_access_iterator<T>& _x, const random_access_iterator<T>& _y) {return (_x.getPtr() >= _y.getPtr());}
	template <typename T>
	bool operator<(const random_access_iterator<T>& _x, const random_access_iterator<T>& _y) {return (_x.getPtr() < _y.getPtr());}
	template <typename T>
	bool operator<=(const random_access_iterator<T>& _x, const random_access_iterator<T>& _y) {return (_x.getPtr() <= _y.getPtr());}

	template <typename T1, typename T2>
	bool operator==(const random_access_iterator<T1>& _x, const random_access_iterator<T2>& _y) {return (_x.getPtr() == _y.getPtr());}
	template <typename T1, typename T2>
	bool operator!=(const random_access_iterator<T1>& _x, const random_access_iterator<T2>& _y) {return (_x.getPtr() != _y.getPtr());}
	template <typename T1, typename T2>
	bool operator>(const random_access_iterator<T1>& _x, const random_access_iterator<T2>& _y) {return (_x.getPtr() > _y.getPtr());}
	template <typename T1, typename T2>
	bool operator>=(const random_access_iterator<T1>& _x, const random_access_iterator<T2>& _y) {return (_x.getPtr() >= _y.getPtr());}
	template <typename T1, typename T2>
	bool operator<(const random_access_iterator<T1>& _x, const random_access_iterator<T2>& _y) {return (_x.getPtr() < _y.getPtr());}
	template <typename T1, typename T2>
	bool operator<=(const random_access_iterator<T1>& _x, const random_access_iterator<T2>& _y) {return (_x.getPtr() <= _y.getPtr());}


/*--------------------------------------- rev_random_access_iterator ---------------------------------------*/
template <typename Iterator>
class rev_random_access_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category, 
													typename ft::iterator_traits<Iterator>::value_type,
													typename ft::iterator_traits<Iterator>::difference_type,
													typename ft::iterator_traits<Iterator>::pointer,
													typename ft::iterator_traits<Iterator>::reference>
{
public:
	typedef Iterator												iterator_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer			pointer;
	typedef typename ft::iterator_traits<Iterator>::reference		reference;

	rev_random_access_iterator() : current() {}
	rev_random_access_iterator(iterator_type _x) : current(_x) {}
	rev_random_access_iterator(const rev_random_access_iterator& _x) : current(_x.getPtr()) {}
	template <typename T1>
	rev_random_access_iterator(const rev_random_access_iterator<T1>& _x) : current(_x.getPtr()) {}

	// rev_random_access_iterator &operator=(const rev_random_access_iterator& _x) {
	// 	if (this != &_x)
	// 		current = _x.current;
	// 	return (*this);
	// }

	~rev_random_access_iterator() {}
	
	iterator_type getPtr() const {return current;}

	reference operator*() const {
		iterator_type	tmp = current;
		return (*(--tmp));
	}
	pointer operator->() const {return &(operator*());}
	rev_random_access_iterator &operator++() {
		--current;
		return (*this);
	}
	rev_random_access_iterator operator++(int) {
		rev_random_access_iterator tmp = *this;
		--current;
		return (tmp);
	}
	rev_random_access_iterator &operator--() {
		++current;
		return (*this);
	}
	rev_random_access_iterator operator--(int) {
		rev_random_access_iterator tmp = *this;
		++current;
		return (tmp);
	}

	reference operator[](difference_type n) const {return (current[n]);}
	rev_random_access_iterator &operator+=(difference_type n) {
		current -= n;
		return (*this);
		}
	rev_random_access_iterator operator-=(difference_type n) {
		current += n;
		return (*this);
		}
	rev_random_access_iterator operator+(difference_type n) {return rev_random_access_iterator(current - n);}
	rev_random_access_iterator operator-(difference_type n) {return rev_random_access_iterator(current + n);}

protected:
	Iterator	current;
};

	template <typename T>
	bool operator==(const rev_random_access_iterator<T>& _x, const rev_random_access_iterator<T>& _y) {return (_x.getPtr() == _y.getPtr());}
	template <typename T>
	bool operator!=(const rev_random_access_iterator<T>& _x, const rev_random_access_iterator<T>& _y) {return (_x.getPtr() != _y.getPtr());}
	template <typename T>
	bool operator>(const rev_random_access_iterator<T>& _x, const rev_random_access_iterator<T>& _y) {return (_x.getPtr() > _y.getPtr());}
	template <typename T>
	bool operator>=(const rev_random_access_iterator<T>& _x, const rev_random_access_iterator<T>& _y) {return (_x.getPtr() >= _y.getPtr());}
	template <typename T>
	bool operator<(const rev_random_access_iterator<T>& _x, const rev_random_access_iterator<T>& _y) {return (_x.getPtr() < _y.getPtr());}
	template <typename T>
	bool operator<=(const rev_random_access_iterator<T>& _x, const rev_random_access_iterator<T>& _y) {return (_x.getPtr() <= _y.getPtr());}

	template <typename T1, typename T2>
	bool operator==(const rev_random_access_iterator<T1>& _x, const rev_random_access_iterator<T2>& _y) {return (_x.getPtr() == _y.getPtr());}
	template <typename T1, typename T2>
	bool operator!=(const rev_random_access_iterator<T1>& _x, const rev_random_access_iterator<T2>& _y) {return (_x.getPtr() != _y.getPtr());}
	template <typename T1, typename T2>
	bool operator>(const rev_random_access_iterator<T1>& _x, const rev_random_access_iterator<T2>& _y) {return (_x.getPtr() > _y.getPtr());}
	template <typename T1, typename T2>
	bool operator>=(const rev_random_access_iterator<T1>& _x, const rev_random_access_iterator<T2>& _y) {return (_x.getPtr() >= _y.getPtr());}
	template <typename T1, typename T2>
	bool operator<(const rev_random_access_iterator<T1>& _x, const rev_random_access_iterator<T2>& _y) {return (_x.getPtr() < _y.getPtr());}
	template <typename T1, typename T2>
	bool operator<=(const rev_random_access_iterator<T1>& _x, const rev_random_access_iterator<T2>& _y) {return (_x.getPtr() <= _y.getPtr());}

}

#endif