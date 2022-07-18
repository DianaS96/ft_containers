#ifndef NODE_HPP
# define NODE_HPP
# include "utils.hpp"

namespace ft
{
    template<typename T>
	struct Node
	{
		Node	*_Left; // left subtree, or smallest element if head
		Node	*_Right; // right subtree, or largest element if head
		Node	*_Parent; // parent, or root of tree if head
		bool	_Color; //Red or Black, Black if head
		T		_Myval; // the stored value, unused if head

        Node(const T & elem, Node *lt = NULL, Node *rt = NULL, Node *par = NULL, bool col = RED) : 
        _Left(lt), _Right(rt), _Parent(par), _Color(col), _Myval(elem) {}
	};
} // namespace ft

#endif