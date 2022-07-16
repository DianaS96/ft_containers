#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include "../src/utils.hpp"
# include <map>

namespace ft
{	
	template<
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	private:
		/* data */
	public:
		/*-------------------- Member types --------------------*/
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef std::pair<const Key, T>				value_type;
		typedef std::size_t							size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef Compare								key_compare;
		typedef Allocator							allocator_type;
		typedef typename value_type&				reference;
		typedef typename const value_type&			const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef Node<value_type>					node;
		typedef node*								node_ptr;
		// iterator	LegacyBidirectionalIterator to value_type
		// const_iterator	LegacyBidirectionalIterator to const value_type
		// reverse_iterator	std::reverse_iterator<iterator>
		// const_reverse_iterator	std::reverse_iterator<const_iterator>


		map(/* args */);
		~map();
	};
	
	map::map(/* args */)
	{
	}
	
	map::~map()
	{
	}
	
} // namespace ft

#endif