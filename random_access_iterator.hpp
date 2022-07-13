#ifndef RANDOM_ACCESS_ITERATOR_TAG_HPP
# define RANDOM_ACCESS_ITERATOR_TAG_HPP

/*https://code.woboq.org/gcc/libstdc++-v3/include/bits/stl_iterator.h.html#_ZNKSt16reverse_iteratorptEv*/
# include "utils.hpp"

namespace ft {

/*--------------------------------------- random_access_iterator ---------------------------------------*/
template <class Iterator>
class random_access_iterator : public ft::iterator<typename ft::iterator_traits<Iterator *>::iterator_category, 
													typename ft::iterator_traits<Iterator *>::value_type,
													typename ft::iterator_traits<Iterator *>::difference_type,
													typename ft::iterator_traits<Iterator *>::pointer,
													typename ft::iterator_traits<Iterator *>::reference>
{
private:
	/* data */
public:
	typedef typename ft::iterator_traits<Iterator *>::pointer					iterator_type;
	typedef typename ft::iterator_traits<Iterator *>::value_type		value_type;
	typedef typename ft::iterator_traits<Iterator *>::difference_type	difference_type;
	typedef typename ft::iterator_traits<Iterator *>::pointer			pointer;
	typedef typename ft::iterator_traits<Iterator *>::reference		reference;

	random_access_iterator() : current(NULL) {}
	random_access_iterator(iterator_type _x) : current(_x) {}
	random_access_iterator(const random_access_iterator& _x) : current(_x.current) {}
	random_access_iterator &operator=(const random_access_iterator& _x) {
		if (this != &_x)
			current = _x.current;
		return (*this);
	}

	~random_access_iterator() {}

	bool operator==(const random_access_iterator& _x) {return (current == _x.current);}
	bool operator!=(const random_access_iterator& _x) {return (current != _x.current);}
	bool operator>(const random_access_iterator& _x) {return (current > _x.current);}
	bool operator>=(const random_access_iterator& _x) {return (current >= _x.current);}
	bool operator<(const random_access_iterator& _x) {return (current < _x.current);}
	bool operator<=(const random_access_iterator& _x) {return (current <= _x.current);}
	
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
	random_access_iterator &operator+(difference_type n) const {return random_access_iterator(current + n);}

	random_access_iterator &operator-(difference_type n) const {return random_access_iterator(current - n);}

	difference_type operator-(const random_access_iterator & rhs)
	{
		return (current - rhs.current);
	}

protected:
	iterator_type	current;
};

/*--------------------------------------- rev_random_access_iterator ---------------------------------------*/
template <class Iterator>
class rev_random_access_iterator : public ft::iterator<typename ft::iterator_traits<Iterator *>::iterator_category, 
													typename ft::iterator_traits<Iterator *>::value_type,
													typename ft::iterator_traits<Iterator *>::difference_type,
													typename ft::iterator_traits<Iterator *>::pointer,
													typename ft::iterator_traits<Iterator *>::reference>
{
private:
	/* data */
public:
	typedef Iterator												iterator_type;
	typedef typename ft::iterator_traits<Iterator>::value_type		value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer			pointer;
	typedef typename ft::iterator_traits<Iterator>::reference		reference;

	rev_random_access_iterator() : current() {}
	rev_random_access_iterator(iterator_type _x) : current(_x) {}
	rev_random_access_iterator(const rev_random_access_iterator& _x) : current(_x.current) {}
	rev_random_access_iterator &operator=(const rev_random_access_iterator& _x) {
		if (this != &_x)
			current = _x.current;
		return (*this);
	}

	~rev_random_access_iterator() {}

	bool operator==(rev_random_access_iterator& _x) {return (current == _x.current);}
	bool operator!=(rev_random_access_iterator& _x) {return (current != _x.current);}
	bool operator>(rev_random_access_iterator& _x) {return (current > _x.current);}
	bool operator>=(rev_random_access_iterator& _x) {return (current >= _x.current);}
	bool operator<(rev_random_access_iterator& _x) {return (current < _x.current);}
	bool operator<=(rev_random_access_iterator& _x) {return (current == _x.current);}
	
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
	rev_random_access_iterator &operator+=(difference_type n) const {
		current -= n;
		return (*this);
		}
	rev_random_access_iterator &operator-=(difference_type n) const {
		current += n;
		return (*this);
		}
	rev_random_access_iterator &operator+(difference_type n) const {rev_random_access_iterator(current - n);}
	rev_random_access_iterator &operator-(difference_type n) const {rev_random_access_iterator(current + n);}

protected:
	Iterator	current;
};

}

#endif