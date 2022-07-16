#ifndef TREEITERATOR_HPP
# define TREEITERATOR_HPP

// https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
// https://cplusplus.com/reference/iterator/BidirectionalIterator/

// # include "RedBlackTree.hpp"
# include "node.hpp"
namespace ft {

/*--------------------------------------- random_access_iterator ---------------------------------------*/
template <class T>
class TreeIterator : public ft::iterator< std::bidirectional_iterator_tag, T>
{
public:

public:    
    // nodePtr is the current location in the tree. we can move
    // freely about the tree using left, right, and parent.
    // root - root pointer of the tree, which is needed for ++ and --
    // when the iterator value is end()
    Node<T> *nodePtr;
	Node<T> *root;
    
    // used to construct an iterator return value from a node pointer
    TreeIterator (const Node<T> *p, const Node<T> *r) : nodePtr(p), root(r) {}
	
	TreeIterator() {}
	TreeIterator(const TreeIterator& other) : nodePtr(other.nodePtr), root(other.root) {}

	TreeIterator &operator=(const TreeIterator& other) {
		nodePtr = other.nodePtr;
		root = other.root;
		return (*this);
	}

	~TreeIterator() {}

	bool operator==(const TreeIterator& rhs) const {return (nodePtr == rhs.nodePtr);}
    
    bool operator!=(const TreeIterator& rhs) const {return (nodePtr != rhs.nodePtr);}
    
    // dereference operator. return a reference to the value pointed to by nodePtr
    T& operator*() {return nodePtr->_Myval;}
    
	T* operator->() {return &(nodePtr->_Myval);}

    // preincrement. move forward to next larger value
	/*If the current node has a non-null right child, Take a step down to the right. Then run down to the left as far as possible
	If the current node has a null right child, move up the tree until we have moved over a left child link*/
    TreeIterator& operator++() {
		if (nodePtr == NULL)
		{
			if (root == NULL)
				return (*this);
			nodePtr = root;
			while (nodePtr->_Left != NULL)
				nodePtr = nodePtr->_Left;
		}
		else {
			if (nodePtr->_Right != NULL)
			{
				nodePtr = nodePtr->_Right;
				while (nodePtr->_Left != NULL)
					nodePtr = nodePtr->_Left;
			}
			else {
				while (nodePtr->_Parent && nodePtr == nodePtr->_Parent->_Right)
					nodePtr = nodePtr->_Parent;
				nodePtr = nodePtr->_Parent;
			}
		}
		return (*this);
	}
    
    // postincrement
    TreeIterator operator++(int) {
		TreeIterator clone(*this);
		++(*this);
		return (clone);
	}
    
    // predecrement. move backward to largest value < current value
    TreeIterator operator--() {
		if (nodePtr == NULL)
		{
			if (root == NULL)
				return (*this);
			nodePtr = root;
			while (nodePtr->_Right != NULL)
				nodePtr = nodePtr->_Right;
		}
		else {
			if (nodePtr->_Left != NULL)
			{
				nodePtr = nodePtr->_Left;
				while (nodePtr->_Right != NULL)
					nodePtr = nodePtr->_Right;
			}
			else {
				while (nodePtr->_Parent && nodePtr == nodePtr->_Parent->_Left)
					nodePtr = nodePtr->_Parent;
				nodePtr = nodePtr->_Parent;
			}
		}
		return (*this);
	}
    
    // postdecrement
    TreeIterator operator--(int) {
		TreeIterator clone(*this);
		--(*this);
		return (clone);
	}

};

template <class T>
class TreeConstIterator : public ft::iterator<std::bidirectional_iterator_tag, T, std::ptrdiff_t, const T*, const T&>
{
public:
	TreeConstIterator() {}
	TreeConstIterator(const TreeConstIterator& other) : nodePtr(other.nodePtr), root(other.root) {}

	TreeConstIterator &operator=(const TreeConstIterator& other) {
		nodePtr = other.nodePtr;
		root = other.root;
		return (*this);
	}

	~TreeConstIterator() {}

	bool operator==(const TreeConstIterator& rhs) const {return (nodePtr == rhs.nodePtr);}
    
    bool operator!=(const TreeConstIterator& rhs) const {return (nodePtr != rhs.nodePtr);}
    
    const T& operator*() const {return nodePtr->_Myval;}
    
	const T* operator->() const {return &(nodePtr->_Myval);}

    TreeConstIterator& operator++() {
		if (nodePtr == NULL)
		{
			if (root == NULL)
				return (*this);
			nodePtr = root;
			while (nodePtr->_Left != NULL)
				nodePtr = nodePtr->_Left;
		}
		else {
			if (nodePtr->_Right != NULL)
			{
				nodePtr = nodePtr->_Right;
				while (nodePtr->_Left != NULL)
					nodePtr = nodePtr->_Left;
			}
			else {
				while (nodePtr->_Parent && nodePtr == nodePtr->_Parent->_Right)
					nodePtr = nodePtr->_Parent;
				nodePtr = nodePtr->_Parent;
			}
		}
		return (*this);
	}
    
    TreeConstIterator operator++(int) {
		TreeConstIterator clone(*this);
		++(*this);
		return (clone);
	}
    
    TreeConstIterator operator--() {
		if (nodePtr == NULL)
		{
			if (root == NULL)
				return (*this);
			nodePtr = root;
			while (nodePtr->_Right != NULL)
				nodePtr = nodePtr->_Right;
		}
		else {
			if (nodePtr->_Left != NULL)
			{
				nodePtr = nodePtr->_Left;
				while (nodePtr->_Right != NULL)
					nodePtr = nodePtr->_Right;
			}
			else {
				while (nodePtr->_Parent && nodePtr == nodePtr->_Parent->_Left)
					nodePtr = nodePtr->_Parent;
				nodePtr = nodePtr->_Parent;
			}
		}
		return (*this);
	}
    
    TreeConstIterator operator--(int) {
		TreeConstIterator clone(*this);
		--(*this);
		return (clone);
	}

public:    
    const Node<T> *nodePtr;
	const Node<T> *root;
    
    TreeConstIterator (const Node<T> *p, const Node<T> *r) : nodePtr(p), root(r) {}
};

// /*--------------------------------------- rev_random_access_iterator ---------------------------------------*/
// template <class Iterator>
// class rev_random_access_iterator : public ft::iterator<typename ft::iterator_traits<Iterator *>::iterator_category, 
// 													typename ft::iterator_traits<Iterator *>::value_type,
// 													typename ft::iterator_traits<Iterator *>::difference_type,
// 													typename ft::iterator_traits<Iterator *>::pointer,
// 													typename ft::iterator_traits<Iterator *>::reference>
// {
// private:
// 	/* data */
// public:
// 	typedef Iterator												iterator_type;
// 	typedef typename ft::iterator_traits<Iterator>::value_type		value_type;
// 	typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
// 	typedef typename ft::iterator_traits<Iterator>::pointer			pointer;
// 	typedef typename ft::iterator_traits<Iterator>::reference		reference;

// 	rev_random_access_iterator() : current() {}
// 	rev_random_access_iterator(iterator_type _x) : current(_x) {}
// 	rev_random_access_iterator(const rev_random_access_iterator& _x) : current(_x.current) {}
// 	rev_random_access_iterator &operator=(const rev_random_access_iterator& _x) {
// 		if (this != &_x)
// 			current = _x.current;
// 		return (*this);
// 	}

// 	~rev_random_access_iterator() {}

// 	bool operator==(const rev_random_access_iterator& _x) {return (current == _x.current);}
// 	bool operator!=(const rev_random_access_iterator& _x) {return (current != _x.current);}
// 	bool operator>(const rev_random_access_iterator& _x) {return (current > _x.current);}
// 	bool operator>=(const rev_random_access_iterator& _x) {return (current >= _x.current);}
// 	bool operator<(const rev_random_access_iterator& _x) {return (current < _x.current);}
// 	bool operator<=(const rev_random_access_iterator& _x) {return (current <= _x.current);}
	
// 	reference operator*() const {
// 		iterator_type	tmp = current;
// 		return (*(--tmp));
// 	}
// 	pointer operator->() const {return &(operator*());}
// 	rev_random_access_iterator &operator++() {
// 		--current;
// 		return (*this);
// 	}
// 	rev_random_access_iterator operator++(int) {
// 		rev_random_access_iterator tmp = *this;
// 		--current;
// 		return (tmp);
// 	}
// 	rev_random_access_iterator &operator--() {
// 		++current;
// 		return (*this);
// 	}
// 	rev_random_access_iterator operator--(int) {
// 		rev_random_access_iterator tmp = *this;
// 		++current;
// 		return (tmp);
// 	}

// 	reference operator[](difference_type n) const {return (current[n]);}
// 	rev_random_access_iterator &operator+=(difference_type n) {
// 		current -= n;
// 		return (*this);
// 		}
// 	rev_random_access_iterator &operator-=(difference_type n) {
// 		current += n;
// 		return (*this);
// 		}
// 	rev_random_access_iterator &operator+(difference_type n) {rev_random_access_iterator(current - n);}
// 	rev_random_access_iterator &operator-(difference_type n) {rev_random_access_iterator(current + n);}

// protected:
// 	Iterator	current;
// };

}

#endif