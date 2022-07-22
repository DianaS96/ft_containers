#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

# include "TreeIterator.hpp"
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
		typedef ft::TreeIterator<value_type>				iterator;
		typedef ft::TreeConstIterator<value_type>			const_iterator;
		typedef ft::TreeReverseIterator<value_type>			reverse_iterator;
		typedef ft::TreeConstReverseIterator<value_type>	const_reverse_iterator;
	
	private:
		allocator_type	_alloc;
		node_allocator	_node_alloc;
		compare			_compare;
		Node			*_root;
		size_type		_size;

	public:
		RedBlackTree() : 
		_alloc(allocator_type()), 
		_node_alloc(node_allocator()), 
		_compare(compare()), 
		_root(NULL), 
		_size(0) {}
		RedBlackTree(const compare & comp, const allocator_type & alloc = allocator_type()) : 
		_alloc(alloc), 
		_node_alloc(node_allocator()), 
		_compare(comp), 
		_root(NULL), 
		_size(0) {}
		RedBlackTree(const RedBlackTree & other) : 
			_alloc(other._alloc), _node_alloc(other._node_alloc), _compare(other._compare), _root(other._root), _size(other._size) {}

		~RedBlackTree() {}

		RedBlackTree& operator=(const RedBlackTree & other) {
			Node	*tmp_tree = NULL;

			_copy_tree(tmp_tree, NULL, other._root);
			_clear_tree(_root);
			_root = tmp_tree;
			_size = other._size;
			return *this;
		}
	
		/*-------------------- Iterators --------------------*/
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;

		size_type size() const {return _size;}
		size_type max_size() const {return _node_alloc.max_size();}
		bool empty() const {return _size == 0;}
		allocator_type get_allocator() const {return _alloc;}

		ft::pair<iterator, bool> insert(const value_type& _Val);
		iterator insert(iterator hint, const value_type& _Val);
		template <class _Iter>
	    void insert(_Iter _First, _Iter _Last);

		void erase(iterator _Where);
		void erase(iterator _First, iterator _Last);
		size_type erase(const value_type& _Keyval);

		void clear() {
			_clear_tree(_root);
			_root = NULL;
		}

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

    	void _copy_tree(Node *&current, Node *parent, Node *other);
		void	_clear_tree(Node *current);
		Node *_Buynode(const value_type & val, Node *parent = NULL, Node *left = NULL, Node *right = NULL, bool color = RED) {
			Node *tmp = _node_alloc.allocate(1);
			_node_alloc.construct(tmp, Node(val, left, right, parent, color));
			_size++;
			return (tmp);
		}

		ft::pair<Node *, bool> _Emplace(Node **tree, const value_type & key);
		void _insertionFix(Node *node);
		void rbTransplant(Node *u, Node *v);
		void _erase_node(Node *node);
		void _fixErase(Node *node);
		void _delete_node(Node *node);
		Node *_find_node(const value_type& _Keyval) const;
	};

	template <class T, class Compare, class Allocator>
	void	RedBlackTree<T, Compare, Allocator>::_copy_tree(Node *&current, Node *curr_parent, Node *other_node)
	{
		if (other_node == NULL)
			return ;
		current = _Buynode(other_node->_Myval, curr_parent, NULL, NULL, RED);
		_copy_tree(current->_Left, current, other_node->_Left);
		_copy_tree(current->_Right, current, other_node->_Right);
	}

	template <class T, class Compare, class Allocator>
	void	RedBlackTree<T, Compare, Allocator>::_clear_tree(Node *current)
	{
		if (current == NULL)
			return ;
		_clear_tree(current->_Left);
		_clear_tree(current->_Right);
		_delete_node(current);
	}

	/* ITERATORS --------------------------------------------------------------------------------------------------------------- */
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
	typename RedBlackTree<T, Compare, Allocator>::reverse_iterator RedBlackTree<T, Compare, Allocator>::rbegin() {
		Node *tmp = _root;
		while (tmp && tmp->_Right)
			tmp = tmp->_Right;
		return reverse_iterator(tmp, _root);
	}

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::reverse_iterator RedBlackTree<T, Compare, Allocator>::rend() {
		Node *tmp = _root;
		while (tmp && tmp->_Left)
			tmp = tmp->_Left;
		if (tmp)
			tmp = tmp->_Left;
		return reverse_iterator(tmp, _root);
	}

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::const_reverse_iterator RedBlackTree<T, Compare, Allocator>::rbegin() const {
		Node *tmp = _root;
		while (tmp && tmp->_Right)
			tmp = tmp->_Right;
		return const_reverse_iterator(tmp, _root);
	}

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::const_reverse_iterator RedBlackTree<T, Compare, Allocator>::rend() const {
		Node *tmp = _root;
		while (tmp && tmp->_Left)
			tmp = tmp->_Left;
		if (tmp)
			tmp = tmp->_Left;
		return const_reverse_iterator(tmp, _root);
	}

	/* FIND --------------------------------------------------------------------------------------------------------------- */
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
	typename RedBlackTree<T, Compare, Allocator>::const_iterator RedBlackTree<T, Compare, Allocator>::find(const value_type& _Keyval) const {
		return (const_iterator(_find_node(_Keyval), _root));
	}

	/* ROTATIONS --------------------------------------------------------------------------------------------------------------- */
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

	/* INSERT --------------------------------------------------------------------------------------------------------------- */
	template <class T, class Compare, class Allocator>
	ft::pair<typename RedBlackTree<T, Compare, Allocator>::iterator, bool> RedBlackTree<T, Compare, Allocator>::insert(const value_type& _Val) {
		ft::pair<Node *, bool> tmp = _Emplace(&_root, _Val);
		return ft::make_pair(iterator(tmp.first, _root), tmp.second);
	}

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::iterator RedBlackTree<T, Compare, Allocator>::insert(typename RedBlackTree<T, Compare, Allocator>::iterator hint, const value_type& _Val) {
		ft::pair<Node *, bool> tmp = _Emplace(&_root, _Val);
		return iterator(tmp.first, _root);
	}

	template <class T, class Compare, class Allocator>
	template <class _Iter>
	void RedBlackTree<T, Compare, Allocator>::insert(_Iter _First, _Iter _Last) {
		for (; _First != _Last; ++_First)
			insert(*_First);
	}

	// https://neerc.ifmo.ru/wiki/index.php?title=%D0%9A%D1%80%D0%B0%D1%81%D0%BD%D0%BE-%D1%87%D0%B5%D1%80%D0%BD%D0%BE%D0%B5_%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE
	template <class T, class Compare, class Allocator>
	ft::pair<typename RedBlackTree<T, Compare, Allocator>::Node *, bool> RedBlackTree<T, Compare, Allocator>::_Emplace(Node **tree, const value_type & key) {
		Node	*parent = NULL;

		if (*tree != NULL)
			parent = (*tree)->_Parent;
		while (*tree != NULL) // move down till we met the greatest myval < key
		{
			parent = *tree;
			if (_compare(key, (*tree)->_Myval)) // true if key < myval;
				tree = &((*tree)->_Left); // go left to find node where myval < key
			else if (_compare((*tree)->_Myval, key))
				tree = &((*tree)->_Right);
			else
				return ft::make_pair(*tree, false);
		}
		*tree = _Buynode(key, parent);
		_insertionFix(*tree);
		return ft::make_pair(*tree, true);
	}
	
	template <class T, class Compare, class Allocator>
	void RedBlackTree<T, Compare, Allocator>::_insertionFix(Node *node) {
		while (node->_Parent && node->_Parent->_Color == RED) /* check whether dad is red */
		{
			if (node == node->_Parent->_Left) /* check whether node is left child */
			{
				if (node->_Parent->_Parent->_Right && node->_Parent->_Parent->_Right->_Color == RED) /* red uncle */
				{
					node->_Parent->_Color = BLACK;
					node->_Parent->_Parent->_Right->_Color = BLACK;
					node->_Parent->_Parent->_Color = RED;
					node = node->_Parent->_Parent;
					continue;
				}
				else // uncle is black or there is no uncle
				{
					node->_Parent->_Color = BLACK;
					node->_Parent->_Parent->_Color = RED;
					_Rrotate(node->_Parent->_Parent);
					break;
				}
			}
			else {
				if (node->_Parent->_Parent->_Left && node->_Parent->_Parent->_Left->_Color == RED) /* red uncle */
				{
					node->_Parent->_Color = BLACK;
					node->_Parent->_Parent->_Left->_Color = BLACK;
					node->_Parent->_Parent->_Color = RED;
					node = node->_Parent->_Parent;
					continue;
				}
				else {
					node->_Parent->_Color = BLACK;
					node->_Parent->_Parent->_Color = RED;
					_Lrotate(node->_Parent->_Parent);
					break;
				}
			}
		}
		_root->_Color = BLACK;
	}

	/* ERASE --------------------------------------------------------------------------------------------------------------- */
	template <class T, class Compare, class Allocator>
	void RedBlackTree<T, Compare, Allocator>::rbTransplant(Node *u, Node *v) {
		if (u == _root)
		{
			_root = v;
			v->_Parent = NULL;
		}
		else {
			if (u == u->_Parent->_Left)
				u->_Parent->_Left = v;
			else
				u->_Parent->_Right = v;
			if (v)
				v->_Parent = u->_Parent;
		}
	}

	template <class T, class Compare, class Allocator>
	void RedBlackTree<T, Compare, Allocator>::_erase_node(Node *node) {
		bool original_color = node->_Color;
		Node *to_delete = node;
		Node *tmp;
		if (node->_Left == NULL)
		{
			tmp = node->_Right;
			rbTransplant(node, node->_Right);
		}
		else if (node->_Right == NULL)
		{
			tmp = node->_Left;
			rbTransplant(node, node->_Left);
		}
		else {
			Node *cp = node;
			node = node->_Right;
			while (node->_Left)
				node = node->_Left;
			original_color = node->_Color;
			tmp = node->_Right;
			if (node->_Parent != cp) {
				rbTransplant(node, node->_Right);
				node->_Right = cp->_Right;
				cp->_Right->_Parent = node;
			}
			rbTransplant(cp, node);
			node->_Left = cp->_Left;
			node->_Left->_Parent = node;
			node->_Color = cp->_Color;
		}
		_delete_node(to_delete);
		if (original_color == BLACK)
			_fixErase(tmp);
	}

	template <class T, class Compare, class Allocator>
	void RedBlackTree<T, Compare, Allocator>::_fixErase( Node *node ) {
		Node *brother;

		while (node && node->_Color == BLACK && node != _root) // node is black and not-root
		{
			if (node == node->_Parent->_Left)
			{
				brother = node->_Parent->_Right;
				if (brother->_Color == RED)
				{
					brother->_Color = BLACK;
					node->_Parent->_Color = RED;
					_Lrotate(node->_Parent);
					brother = node->_Parent->_Right;
				}
				if (brother && brother->_Left && brother->_Right &&
					brother->_Left->_Color == BLACK && brother->_Right->_Color == BLACK)
				{
					brother->_Color = RED;
					node = node->_Parent;
				}
				else 
				{
					if (brother && brother->_Right && brother->_Right->_Color == BLACK)
					{
						brother->_Left->_Color = BLACK;
						brother->_Color = RED;
						_Rrotate(brother);
					}
					brother->_Color = brother->_Parent->_Color;
					node->_Parent->_Color = BLACK;
					brother->_Right->_Color = BLACK;
					_Lrotate(node->_Parent);
					node = _root;
				}
			}
			else
			{
				brother = node->_Parent->_Left;
				if (brother && brother->_Color == RED)
				{
					brother->_Color = BLACK;
					node->_Parent->_Color = RED;
					_Rrotate(node->_Parent);
					brother = node->_Parent->_Left;
				}
				if (brother && brother->_Left && brother->_Right &&
					brother->_Left->_Color == BLACK && brother->_Right->_Color == BLACK)
				{
					brother->_Color = RED;
					node = node->_Parent;
				}
				else {
					if (brother && brother->_Left && brother->_Left->_Color == BLACK)
					{
						brother->_Right->_Color = BLACK;
						brother->_Color = RED;
						_Lrotate(brother);
						brother = brother->_Parent->_Left;
					}
					brother->_Color = node->_Parent->_Color;
					node->_Parent->_Color = BLACK;
					brother->_Left->_Color = BLACK;
					_Rrotate(node->_Parent);
					node = _root;
				}
			}			
		}
		if (node)
			node->_Color = BLACK;
		_root->_Color = BLACK;
	}

	template <class T, class Compare, class Allocator>
	void RedBlackTree<T, Compare, Allocator>::erase(iterator _Where) {
		_erase_node(_Where.nodePtr);
	}

	template <class T, class Compare, class Allocator>
	void RedBlackTree<T, Compare, Allocator>::erase(iterator _First, iterator _Last) {
		for (; _First != _Last;)
			_erase_node((_First++).nodePtr);
	}

	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::size_type RedBlackTree<T, Compare, Allocator>::erase(const value_type& _Keyval) {
		Node *found = _find_node(_Keyval);

		if (!found)
			return 0;
		_erase_node(found);
		return 1;
	}


	/* LOWER AND UPPER BOUND, EQUAL RANGE --------------------------------------------------------------------------------------------------------------- */
	// https://en.cppreference.com/w/cpp/algorithm/lower_bound
	// Returns an iterator pointing to the first element that does not satisfy element < _Keyval (or comp(element, _Keyval)), 
	// (i.e. greater or equal to), or last if no such element is found.
	template <class T, class Compare, class Allocator>
	typename RedBlackTree<T, Compare, Allocator>::iterator 
			RedBlackTree<T, Compare, Allocator>::lower_bound(const value_type& _Keyval) {
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

	/* OTHER FUNCTONS --------------------------------------------------------------------------------------------------------------- */
	
	template <class T, class Compare, class Allocator>
	void RedBlackTree<T, Compare, Allocator>::_delete_node(Node *node) {
		_node_alloc.destroy(node);
		_node_alloc.deallocate(node, 1);
		_size -= 1;
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