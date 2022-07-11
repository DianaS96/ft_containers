#ifndef RANDOM_ACCESS_ITERATOR_TAG_HPP
# define RANDOM_ACCESS_ITERATOR_TAG_HPP

/*https://code.woboq.org/gcc/libstdc++-v3/include/bits/stl_iterator.h.html#_ZNKSt16reverse_iteratorptEv*/
# include "utils.hpp"

namespace ft {

template <class Iterator>
class random_access_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category, 
													typename ft::iterator_traits<Iterator>::value_type,
													typename ft::iterator_traits<Iterator>::difference_type,
													typename ft::iterator_traits<Iterator>::pointer,
													typename ft::iterator_traits<Iterator>::reference>
{
private:
	/* data */
public:
	typedef Iterator												iterator_type;
	typedef typename ft::iterator_traits<Iterator>::value_type		value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer			pointer;
	typedef typename ft::iterator_traits<Iterator>::reference		reference;

	random_access_iterator() : current() {}
	random_access_iterator(iterator_type _x) : current(_x) {}
	random_access_iterator(const random_access_iterator& _x) : current(_x.current) {}
	random_access_iterator &operator=(const random_access_iterator& _x) {
		if (this != &_x)
			current = _x.current;
		return (*this);
	}

	~random_access_iterator();

	bool operator==(random_access_iterator& _x) {return (current == _x.current);}
	bool operator!=(random_access_iterator& _x) {return (current != _x.current);}
	bool operator>(random_access_iterator& _x) {return (current > _x.current);}
	bool operator>=(random_access_iterator& _x) {return (current >= _x.current);}
	bool operator<(random_access_iterator& _x) {return (current < _x.current);}
	bool operator<=(random_access_iterator& _x) {return (current == _x.current);}
	
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
	random_access_iterator &operator+=(difference_type n) const {
		current += n;
		return (*this);
		}
	random_access_iterator &operator-=(difference_type n) const {
		current -= n;
		return (*this);
		}
	random_access_iterator &operator+(difference_type n) const {random_access_iterator(current + n);}
	random_access_iterator &operator-(difference_type n) const {random_access_iterator(current - n);}

protected:
	Iterator	current;
};

}

#endif