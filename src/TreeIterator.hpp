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
    // nodePtr is the current location in the tree. we can move
    // freely about the tree using left, right, and parent.
    // root - root pointer of the tree, which is needed for ++ and --
    // when the iterator value is end()
    typedef Node<T> Node;
	Node *nodePtr;
	Node *root;
    
    // used to construct an iterator return value from a node pointer
    TreeIterator (Node *p, Node *r) : nodePtr(p), root(r) {};
	
	TreeIterator() {};
	TreeIterator(const TreeIterator& other) : nodePtr(other.nodePtr), root(other.root) {};

	TreeIterator &operator=(const TreeIterator& other) {
		nodePtr = other.nodePtr;
		root = other.root;
		return (*this);
	}

	~TreeIterator() {}

	friend bool operator==(TreeIterator lhs, TreeIterator rhs) {return (lhs.nodePtr == rhs.nodePtr);}
    
    friend bool operator!=(TreeIterator lhs, TreeIterator rhs) {return (lhs.nodePtr != rhs.nodePtr);}
    
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
    typedef Node<T> Node;
	Node *nodePtr;
	Node *root;
    
    TreeConstIterator (const Node *p, const Node *r) : nodePtr(p), root(r) {}
	TreeConstIterator() {};
	TreeConstIterator(const TreeConstIterator& other) : nodePtr(other.nodePtr), root(other.root) {}

	TreeConstIterator &operator=(const TreeConstIterator& other) {
		nodePtr = other.nodePtr;
		root = other.root;
		return (*this);
	}

	~TreeConstIterator() {}

	friend bool operator==(TreeConstIterator lhs, TreeConstIterator rhs) {return (lhs.nodePtr == rhs.nodePtr);}
    
    friend bool operator!=(TreeConstIterator lhs, TreeConstIterator rhs) {return (lhs.nodePtr != rhs.nodePtr);}
    
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

};

}

#endif