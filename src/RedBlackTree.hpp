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
		const_iterator find(const value_type& _Keyval) const;

		iterator lower_bound(const value_type& _Keyval);
		const_iterator lower_bound(const value_type& _Keyval) const;

		iterator upper_bound(const value_type& _Keyval);
		const_iterator upper_bound(const value_type& _Keyval) const;

		ft::pair<iterator, iterator> equal_range(const value_type& _Keyval);
		ft::pair<const_iterator, const_iterator> equal_range(const value_type& _Keyval) const;

		void swap(RedBlackTree & other);
	
	protected:
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

		ft::pair<Node *, bool> _Emplace(Node **tree, const value_type & key);
		void _insertionFix(Node *node);

		void _remove_node(Node *node);
		Node *_find_node(const value_type& _Keyval) const;
	};

	/* We find the begin() position by starting from the root and working our way down, 
	always taking left children, until we come to a node with no left child. */
	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::iterator RedBlackTree<T, Compare, Allocator>::begin() {
		Node *tmp = _root;
		while (tmp && tmp->_Left)
			tmp = tmp->_Left;
		return iterator(tmp, _root);
	}

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::iterator RedBlackTree<T, Compare, Allocator>::end() {return iterator(NULL, _root);}

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::const_iterator RedBlackTree<T, Compare, Allocator>::begin() const {
		Node *tmp = _root;
		while (tmp && tmp->_Left)
			tmp = tmp->_Left;
		return const_iterator(tmp, _root);
	}
	
	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::const_iterator RedBlackTree<T, Compare, Allocator>::end() const {return const_iterator(NULL, _root);}

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
	void RedBlackTree<T, Compare, Allocator>::_remove_node(Node *node) {
		_node_alloc.destroy(node);
		_node_alloc.destruct(node, 1);
		_size -= 1;
	}

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::iterator RedBlackTree<T, Compare, Allocator>::find(const value_type& _Keyval) {
		return (iterator(_find_node(_Keyval), _root));
	}

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::const_iterator RedBlackTree<T, Compare, Allocator>::find(const value_type& _Keyval) const {
		return (const_iterator(_find_node(_Keyval), _root));
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

	template <class T, class Compare, class Allocator>
	ft::pair<typename RedBlackTree<T, Compare, Allocator>::iterator, bool> RedBlackTree<T, Compare, Allocator>::insert(const value_type& _Val) {
		ft::pair<Node *, bool> tmp = _Emplace(&_root, _Val);
		return ft::make_pair(iterator(tmp.first), tmp.second);
	}
	// iterator insert(iterator hint, const value_type& _Val);
	// template <class _Iter>
	// void insert(_Iter _First, _Iter _Last);

	// https://neerc.ifmo.ru/wiki/index.php?title=%D0%9A%D1%80%D0%B0%D1%81%D0%BD%D0%BE-%D1%87%D0%B5%D1%80%D0%BD%D0%BE%D0%B5_%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE
	template <class T, class Compare, class Allocator>
	ft::pair<typename RedBlackTree<T, Compare, Allocator>::Node *, bool> RedBlackTree<T, Compare, Allocator>::_Emplace(Node **tree, const value_type & key) {
		Node *parent;
		if (*tree == NULL)
			*parent = NULL;
		else {
			*parent = (*tree)->_Parent;
			while (*tree) // move down till we met 
			{
				parent = *tree;
				if (_compare(key, (*tree)->_Myval)) // true if key < myval;
					*tree = &(*tree)->_Left; // go left to find node where myval < key
				else if (_compare((*tree)->_Myval), key)
					*tree = &(*tree)->_Right;
				else
					return ft::make_pair(*tree, true);
			}

		}
		*tree = _Buynode(key, parent, NULL, NULL, RED);
		_insertionFix(*tree);
		return ft::make_pair(*tree, true);
	}
	
	template <class T, class Compare, class Allocator>
	void RedBlackTree<T, Compare, Allocator>::_insertionFix(Node *node) {
		while (node->_Parent && node->_Parent->_Color == RED) /* check whether dad is red */
		{
			if (node->_Parent == node->_Parent->_Parent->_Left) /* check whether dad is left child */
			{
				if (node->_Parent->_Parent->_Right && node->_Parent->_Parent->_Right->_Color == RED) /* red uncle */
				{
					node->_Parent->_Color = BLACK;
					node->_Parent->_Parent->_Right->_Color = BLACK;
					node->_Parent->_Parent = RED;
					node = node->_Parent->_Parent;
					continue;
				}
				else 
				{
					if (node = node->_Parent->_Right)
					{
						node = node->_Parent;
						_Lrotate(node);
					}
					node->_Parent->_Color = BLACK;
					node->_Parent->_Parent = RED;
					_Rrotate(node->_Parent->_Parent);
					break;
				}
			}
			else {
				if (node->_Parent->_Parent->_Left && node->_Parent->_Parent->_Left->_Color == RED)
				{
					node->_Parent->_Color = BLACK;
					node->_Parent->_Parent->_Right->_Color = BLACK;
					node->_Parent->_Parent = RED;
					node = node->_Parent->_Parent;
					continue;	
				}
				else {
					if (node = node->_Parent->_Left)
					{
						node = node->_Parent;
						_Rrotate(node);
					}
					node->_Parent->_Color = BLACK;
					node->_Parent->_Parent = RED;
					_Lrotate(node->_Parent->_Parent);
					break;
				}
			}
		}
		_root->_Color = BLACK;
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

	// https://en.cppreference.com/w/cpp/algorithm/equal_range
	// Returns a range containing all elements equivalent to value in the range [first, last)
	template <class T, class Compare, class Allocator>
	ft::pair<typename RedBlackTree<T, Compare, Allocator>::iterator, typename RedBlackTree<T, Compare, Allocator>::iterator> 
	RedBlackTree<T, Compare, Allocator>::equal_range(const value_type& _Keyval) {
		return (ft::make_pair(lower_bound(_Keyval), upper_bound(_Keyval)));
	}

	template <class T, class Compare, class Allocator>
	ft::pair<typename RedBlackTree<T, Compare, Allocator>::const_iterator, typename RedBlackTree<T, Compare, Allocator>::const_iterator> 
	RedBlackTree<T, Compare, Allocator>::equal_range(const value_type& _Keyval) const {
		return (ft::make_pair(lower_bound(_Keyval), upper_bound(_Keyval)));
	}

	template <class T, class Compare, class Allocator>
	void RedBlackTree<T, Compare, Allocator>::swap(RedBlackTree & other) {
		std::swap(_alloc, other._alloc);
		std::swap(_node_alloc, other._node_alloc);
		std::swap(_compare, other._compare);
		std::swap(_root, other._root);
		std::swap(_size, other._size);
	}
}
#endif