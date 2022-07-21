#ifndef SET_HPP
# define SET_HPP

#include "../src/utils.hpp"
# include "../src/RedBlackTree.hpp"

#include <set>
namespace ft {
	template<
	class Key,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<Key>
	> class set
	{
	public:
		/*-------------------- MEMBER TYPES --------------------*/
		typedef Key									key_type;
		typedef Key									value_type;
		typedef std::size_t							size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef Compare								key_compare;
		typedef Compare								value_compare;
		typedef Allocator							allocator_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		typedef typename ft::RedBlackTree<Key, Compare, Allocator>::iterator				iterator;
		typedef typename ft::RedBlackTree<Key, Compare, Allocator>::const_iterator			const_iterator;
		typedef typename ft::RedBlackTree<Key, Compare, Allocator>::reverse_iterator		reverse_iterator;
		typedef typename ft::RedBlackTree<Key, Compare, Allocator>::const_reverse_iterator	const_reverse_iterator;
		
		typedef RedBlackTree<Key, Compare, Allocator>	rbtree;

		/*-------------------- MEMBER FUNCTIONS --------------------*/

		set() : _comp(key_compare()), _alloc(allocator_type()), _tree() {}
		explicit set( const Compare& comp, const Allocator& alloc = Allocator() ) : _comp(comp), _alloc(alloc), _tree(comp, alloc) {}
		set( const set& other ) : _comp(other._comp), _alloc(other._alloc), _tree(other._tree) {}
		template< class InputIt >
		set( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : _comp(comp), _alloc(alloc) {
			_tree(first, last);
		}

		~set();

		set& operator=( const set& other ) {
			_tree = other._tree;
			return *this;
		}

		allocator_type get_allocator() const {return _alloc;}

		/*-------------------- Iterators --------------------*/
		iterator begin() {return _tree.begin();}
		const_iterator begin() const {return _tree.begin();}
		iterator end() {return _tree.end();}
		const_iterator end() const {return _tree.end();}
		reverse_iterator rbegin() {return _tree.rbegin();}
		const_reverse_iterator rbegin() const {return _tree.rbegin();}
		reverse_iterator rend() {return _tree.rend();}
		const_reverse_iterator rend() const {return _tree.rend();}

		/*-------------------- Capacity --------------------*/
		bool empty() const {return _tree.empty();}
		size_type size() const {return _tree.size();}
		size_type max_size() const {return _tree.max_size();}

		/*-------------------- Modifiers --------------------*/
		void clear() {_tree.clear();}
		
		ft::pair<iterator,bool> insert( const value_type& value ) {return _tree.insert(value);}
		iterator insert( iterator hint, const value_type& value ) {return _tree.insert(hint, value);}
		template< class InputIt >
		void insert( InputIt first, InputIt last ) {_tree.insert(first, last);}

		void erase( iterator pos ) {_tree.erase(pos);}
		void erase( iterator first, iterator last ) {_tree.erase(first, last);}
		size_type erase( const Key& key ) {return _tree.erase(key);}

		void swap( set& other ) {_tree.swap(other._tree);}

		/*-------------------- Lookup --------------------*/
		size_type count( const Key& key ) const {
			if (_tree.find(key))
				return 1;
			return 0;
		}

		iterator find( const Key& key ) {return _tree.find(key);}
		const_iterator find( const Key& key ) const {return _tree.find(key);}

		ft::pair<iterator,iterator> equal_range( const Key& key ) {return _tree.equal_range(key);}
		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {return _tree.equal_range(key);}

		iterator lower_bound( const Key& key ) {return _tree.lower_bound(key);}
		const_iterator lower_bound( const Key& key ) const {return _tree.lower_bound(key);}

		iterator upper_bound( const Key& key ) {return _tree.upper_bound(key);}
		const_iterator upper_bound( const Key& key ) const {return _tree.upper_bound(key);}

		/*-------------------- Observers --------------------*/
		key_compare key_comp() const {return _comp;}
		value_compare value_comp() const {return _comp;}

		protected:
			key_compare		_comp;
			allocator_type	_alloc;
			rbtree			_tree;
	};

	template< class Key, class Compare, class Allocator >
	bool operator==(const set<Key, Compare, Allocator>& __x,
        			const set<Key, Compare, Allocator>& __y)
	{
		return (__x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin()));
	}

	template< class Key, class Compare, class Allocator >
	bool operator!=(const set<Key, Compare, Allocator>& __x,
        			const set<Key, Compare, Allocator>& __y)
	{
		return !(__x == __y);
	}

	template< class Key, class Compare, class Allocator >
	bool operator<(const set<Key, Compare, Allocator>& __x,
        			const set<Key, Compare, Allocator>& __y)
	{
		return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
	}

	template< class Key, class Compare, class Allocator >
	bool operator>(const set<Key, Compare, Allocator>& __x,
        			const set<Key, Compare, Allocator>& __y)
	{
		return !(__x < __y || __x == __y);
	}

	template< class Key, class Compare, class Allocator >
	bool operator>=(const set<Key, Compare, Allocator>& __x,
        			const set<Key, Compare, Allocator>& __y)
	{
		return !(__x < __y);
	}

	template< class Key, class Compare, class Allocator >
	bool operator<=(const set<Key, Compare, Allocator>& __x,
        			const set<Key, Compare, Allocator>& __y)
	{
		return (__x < __y || __x == __y);
	}

	template< class Key, class Compare, class Allocator >
	void swap( set<Key, Compare, Allocator>& lhs,
           		set<Key, Compare, Allocator>& rhs ) {
		lhs.swap(rhs);
	}	
}

#endif