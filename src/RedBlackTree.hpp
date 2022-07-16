#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

// # include "TreeIterator.hpp"
# include "utils.hpp"

// https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
// https://russianblogs.com/article/1327503951/
// http://mech.math.msu.su/~vvb/2course/Borisenko/lecTree.html
namespace ft {

	template <class T>
	class TreeIterator;

	template <class T>
	class TreeConstIterator;

	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class RedBlackTree
	{
	public:
		typedef T														value_type;
		typedef Allocator												allocator_type;
		typedef Compare													compare;
		typedef std::size_t												size_type;
		typedef Node<value_type>										Node;
		typedef typename allocator_type::template rebind<Node>::other	node_allocator;
		
		/*-------------------- Iterators --------------------*/
		typedef ft::TreeIterator<value_type>			iterator;
		typedef TreeConstIterator<value_type>			const_iterator;
		// typedef TreeIterator<value_type>				reverse_iterator;
		// typedef TreeConstIterator<value_type>				const_reverse_iterator;
	
	private:
		allocator_type	_alloc;
		node_allocator	_node_alloc;
		compare			_compare;
		Node			*_root;
		size_type		_size;

	public:
		RedBlackTree() : _alloc(allocator_type()), _node_alloc(node_allocator()), _compare(compare()), _root(NULL), _size(0) {}
		explicit RedBlackTree(const compare & comp = compare(), const allocator_type & alloc = allocator_type()) : 
		_alloc(alloc), _node_alloc(node_allocator()), _compare(comp), _root(NULL), _size(0) {}
		RedBlackTree(const RedBlackTree & other);

		~RedBlackTree();

		RedBlackTree& operator=(const RedBlackTree & other);
	
		/*-------------------- Iterators --------------------*/
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		// reverse_iterator rbegin();
		// reverse_iterator rend();
		// const_reverse_iterator rbegin() const;
		// const_reverse_iterator rend() const;

		size_type size() const {return _size;}
		size_type max_size() const {return _node_alloc.max_size();}
		bool empty() const {return _size == 0;}
		allocator_type get_allocator() const {return _alloc;}

		ft::pair<iterator, bool> insert(const value_type& _Val);
		iterator insert(iterator hint, const value_type& _Val);
		template <class _Iter>
	    void insert(_Iter _First, _Iter _Last);

		iterator erase(iterator _Where);
		iterator erase(iterator _First, iterator _Last);
		size_type erase(const value_type& _Keyval);

		void clear();

		iterator find(const value_type& _Keyval);
		// const_iterator find(const value_type& _Keyval) const;

		iterator lower_bound(const value_type& _Keyval);
		const_iterator lower_bound(const value_type& _Keyval) const;

		iterator upper_bound(const value_type& _Keyval);
		const_iterator upper_bound(const value_type& _Keyval) const;

		ft::pair<iterator, iterator> equal_range(const value_type& _Keyval);
		// ft::pair<const_iterator, const_iterator> equal_range(const value_type& _Keyval);

		void swap(RedBlackTree & _Right);
	
	public:
		Node *_Max(Node *_Pnode);
		Node *_Min(Node *_Pnode);

		void _Lrotate(Node *node);
		void _Rrotate(Node *node);

    	Node *_Copy_nodes(Node *current, Node * parent, Node *other);
		Node *_Buynode(const value_type & val, Node *parent = NULL, Node *left = NULL, Node *right = NULL, bool color = RED) {
			Node *tmp = _node_alloc.allocatw(1);
			_node_alloc.construct(tmp, Node(val, left, right, parent, color));
			_size++;
			return (tmp);
		}

		Node *_find_node(const value_type& _Keyval) const;
	};

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::Node *RedBlackTree<T, Compare, Allocator>::_find_node(const value_type& _Keyval) const {
		Node *tmp = _root;

		while (tmp != NULL)
		{
			if (_compare(_Keyval, tmp->_Myval))
				tmp = tmp->_Left;
			else if (_compare(tmp->_Myval, _Keyval))
				tmp = tmp->_Right;
			else
				return (tmp);
		}
		return (NULL);
	}

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::iterator RedBlackTree<T, Compare, Allocator>::find(const value_type& _Keyval) {
		return (iterator(_find_node(_Keyval), _root));
	}


	template <class T, class Compare, class Allocator>
	void RedBlackTree<T, Compare, Allocator>::_Lrotate(Node *node) {
		Node *tmp = node->_Right;

		node->_Right = tmp->_Left;
		if (tmp->_Left)
			tmp->_Left->_Parent = node;
		tmp->_Parent = node->_Parent;
		tmp->_Left = node;
		node->_Parent = tmp;
		if (tmp->_Parent)
		{
			if (tmp->_Parent->_Right == tmp->_Left)
				tmp->_Parent->_Right = tmp;
			else
				tmp->_Parent->_Left = tmp;
		}
		else
			_root = tmp;
	}

	template <class T, class Compare, class Allocator>
	void RedBlackTree<T, Compare, Allocator>::_Rrotate(Node *node) {
		Node *tmp = node->_Left;

		node->_Left = tmp->_Right;
		if (tmp->_Right)
			tmp->_Right->_Parent = node;
		tmp->_Parent = node->_Parent;
		tmp->_Right = node;
		node->_Parent = tmp;
		if (tmp->_Parent)
		{
			if (tmp->_Parent->_Left == tmp->_Right)
				tmp->_Parent->_Left = tmp;
			else
				tmp->_Parent->_Right = tmp;
		}
		else
			_root = tmp;
	}

	// https://en.cppreference.com/w/cpp/algorithm/lower_bound
	// Returns an iterator pointing to the first element that does not satisfy element < _Keyval (or comp(element, _Keyval)), 
	// (i.e. greater or equal to), or last if no such element is found.
	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::iterator RedBlackTree<T, Compare, Allocator>::lower_bound(const value_type& _Keyval) {
		Node *tmp = _root;
		Node *res = NULL;

		while (tmp)
		{
			if (_compare(tmp->_Myval, _Keyval)) // true if Myval < Keyval.
				tmp = tmp->_Right;
			else {
				res = tmp;
				tmp = tmp->_Left;
			}
		}
		return (iterator(res, _root));
	}

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::const_iterator RedBlackTree<T, Compare, Allocator>::lower_bound(const value_type& _Keyval) const {
		Node *tmp = _root;
		Node *res = NULL;

		while (tmp)
		{
			if (_compare(tmp->_Myval, _Keyval)) // true if Myval < Keyval.
				tmp = tmp->_Right;
			else {
				res = tmp;
				tmp = tmp->_Left;
			}
		}
		return (const_iterator(res, _root));
	}

	// https://en.cppreference.com/w/cpp/algorithm/upper_bound
	// Returns an iterator pointing to the first element such that value < element 
	// (or comp(value, element)) is true (i.e. strictly greater)
	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::iterator RedBlackTree<T, Compare, Allocator>::upper_bound(const value_type& _Keyval) {
		Node *tmp = _root;
		Node *res = NULL;

		while (tmp)
		{
			if (_compare(_Keyval, tmp->_Myval)) // true if Myval > Keyval.
			{
				res = tmp;
				tmp = tmp->_Left;
			}
			else {
				tmp = tmp->_Right;
			}
		}
		return (iterator(res, _root));
	}

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::const_iterator RedBlackTree<T, Compare, Allocator>::upper_bound(const value_type& _Keyval) const {
		Node *tmp = _root;
		Node *res = NULL;

		while (tmp)
		{
			if (_compare(_Keyval, tmp->_Myval)) // true if Myval > Keyval.
			{
				res = tmp;
				tmp = tmp->_Left;
			}
			else {
				tmp = tmp->_Right;
			}
		}
		return (const_iterator(res, _root));
	}



}
#endif