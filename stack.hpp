#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

#include <stack>

namespace ft
{
	template < class T, class Container = ft::vector<T>>
	class stack
	{
	public:
		/*-------------------- MEMBER TYPES --------------------*/
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		/*-------------------- MEMBER FUNCTIONS --------------------*/
		explicit stack( const Container& cont = Container() ) : container(cont) {}
		stack( const stack& other ) : container(other.container) {}
		
		stack& operator=( const stack& other ) {
			if (this != &other)
				container = other.container;
			return (*this);
		}

		~stack() {}

		/*-------------------- Element access --------------------*/
		reference top() {return container.back();}
		const_reference top() const {return container.back();}

		/*-------------------- Capacity --------------------*/
		bool empty() const {return container.empty();}
		size_type size() const {return container.size();}

		/*-------------------- Modifiers --------------------*/
		void push( const value_type& value ) {container.push_back(value);}
		void pop() {container.pop_back();}

	protected:
		Container	container;
	};
		
} // namespace ft

#endif