#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include "../src/utils.hpp"
# include <map>
# include "../src/RedBlackTree.hpp"
// # include "../src/TreeIterator.hpp"

namespace ft
{	
	template <class Key, class T, class Compare>
	struct PairCompare
	{
		bool	operator()(const ft::pair<const Key, T> & first, const ft::pair<const Key, T> & second) const
		{
			return Compare()(first.first, second.first);
		}
	};

	template<
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		/*-------------------- Member types --------------------*/
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef ft::pair<const Key, T>				value_type;
		typedef std::size_t							size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef Compare								key_compare;
		typedef Allocator							allocator_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef PairCompare<Key, T, Compare>		pair_compare;


		typedef Node<value_type>					node;
		typedef node*								node_ptr;
		typedef ft::TreeIterator<ft::pair<const Key, T> >		iterator;
		typedef ft::TreeConstIterator<ft::pair<const Key, T> >	const_iterator;
		// reverse_iterator	std::reverse_iterator<iterator>
		// const_reverse_iterator	std::reverse_iterator<const_iterator>
		
		/* MEMBER CLASSES -----------------------------------------------*/
		class value_compare: std::binary_function<value_type, value_type, bool>
		{
			friend class map<key_type, mapped_type, key_compare, allocator_type>;
			protected:
				Compare	comp;
				value_compare( Compare c ) : comp(c) {}
			public:
				bool operator()( const value_type& lhs, const value_type& rhs ) const {return (comp(lhs.first, rhs.first));}
		};

		typedef RedBlackTree<ft::pair<const Key, T>, pair_compare, Allocator>	rbtree;

	private:
		allocator_type	_alloc;
		key_compare		_comp;
		rbtree			_tree;

	public:
		/* MEMBER FUNCTIONS -----------------------------------------------*/
		map() : 
			_alloc(allocator_type()), 
			_comp(key_compare()), 
			_tree() {}
		explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : 
			_alloc(alloc), 
			_comp(comp),
			_tree(comp, alloc) {}
		template< class InputIt >
		map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : _alloc(alloc), _comp(comp), _tree(comp, alloc) {
			_tree.insert(first, begin);
		}
		map( const map& other ) : _alloc(other._alloc), _comp(other._comp), _tree(other._tree) {}

		~map() {}

		map& operator=( const map& other ) {
			if (this != &other) {
				_alloc = other._alloc;
				_comp = other._comp;
				_tree = other._tree;
			}
			return (*this);
		}

		allocator_type get_allocator() const {return _alloc;}

		/* Element access -----------------------------------------------*/
		mapped_type& at( const key_type& key ) {
			iterator it = find(key);
			if (it == end())
				throw std::out_of_range("invalid map<K, T> key");
			return it->second;
		}
		const mapped_type& at( const key_type& key ) const {
			const_iterator it = find(key);
			if (it == end())
				throw std::out_of_range("invalid map<K, T> key");
			return it->second;
		}
		T& operator[]( const Key& key ) {
			ft::pair<iterator, bool> it = insert(ft::make_pair(key, T()));
			return (it.first)->second;
		}

		/* Iterators -----------------------------------------------*/
		iterator begin() {return _tree.begin();}
		const_iterator begin() const {return _tree.begin();}
		iterator end() {return _tree.end();}
		const_iterator end() const {return _tree.end();}
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;

		/* Capacity -----------------------------------------------*/
		bool empty() const {return _tree.empty();}
		size_type size() const {return _tree.size();}
		size_type max_size() const {return _tree.max_size();}

		/* Modifiers -----------------------------------------------*/
		void clear() {_tree.clear();}

		ft::pair<iterator, bool> insert( const value_type& value ) {
			return _tree.insert(value);
		}
		iterator insert( iterator hint, const value_type& value ) {_tree.insert(hint, value);}
		template< class InputIt >
		void insert( InputIt first, InputIt last ) {_tree.insert(first, last);}

		void erase( iterator pos ) {_tree.erase(pos);}
		void erase( iterator first, iterator last ) {_tree.erase(first, last);}
		size_type erase( const Key& key ) {return _tree.erase(ft::make_pair(key, mapped_type()));}

		void swap( map& other ) {
			_tree.swap(other._tree);
			// std::swap(_tree, other._tree);
			// std::swap(_alloc, other._alloc);
			// std::swap(_comp, other._comp);
		}

		/* Lookup -----------------------------------------------*/
		size_type count( const Key& key ) const {
			if (find(key) == end())
				return 0;
			return 1;
		}
		iterator find( const Key& key ) {return _tree.find(ft::make_pair(key, mapped_type()));}
		const_iterator find( const Key& key ) const {return _tree.find(ft::make_pair(key, mapped_type()));}

		ft::pair<iterator,iterator> equal_range( const Key& key ) {return _tree.equal_range(ft::make_pair(key, mapped_type()));}
		std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {return _tree.equal_range(ft::make_pair(key, mapped_type()));}

		iterator lower_bound( const Key& key ) {return _tree.lower_bound(ft::make_pair(key, mapped_type()));}
		const_iterator lower_bound( const Key& key ) const {return _tree.lower_bound(ft::make_pair(key, mapped_type()));}

		iterator upper_bound( const Key& key ) {return _tree.upper_bound(ft::make_pair(key, mapped_type()));}
		const_iterator upper_bound( const Key& key ) const {return _tree.upper_bound(ft::make_pair(key, mapped_type()));}

		/* Lookup -----------------------------------------------*/
		/*
		https://en.cppreference.com/w/cpp/container/map/key_comp
		Returns the function object that compares the keys, which is a copy of this container's constructor argument comp.
		*/
		key_compare key_comp() const {return _comp;}
		/*
		https://en.cppreference.com/w/cpp/container/map/value_comp
		Returns a function object that compares objects of type std::map::value_type (key-value pairs) 
		by using key_comp to compare the first components of the pairs.
		*/
		value_compare value_comp() const {return value_compare(key_comp());}
	};
		
} // namespace ft

#endif