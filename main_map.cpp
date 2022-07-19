// #include <iostream>
// namespace ft = std;
// #include <map>
#include "containers/map.hpp"
// /*fonts color*/
// # define FBLACK		"\033[0;30m"
// # define FRED		"\033[0;31m"
// # define FGREEN		"\033[0;32m"
// # define FYELLOW	"\033[0;33m"
// # define FBLUE		 "\033[0;34m"
// # define FPURPLE	"\033[0;35m"
// # define FCYAN		"\x1b[36m"

// /*end color*/
// # define NONE        "\033[0m"

// #define WRONG_SIZE_CAP	"Wrong size or capacity!"
// #define SIZE_CAP_OK		"Size and capacity are ok"

// #define	SIZE_CAP_HEADER	"Size and capacity"

// #define NO_RETURN_VALUE		0
// #define OK_RETURN_VALUE		1
// #define BAD_RETURN_VALUE	2

// #define ZERO_TIME	"N/A - ft_time or std_time == 0"

// # define	SIZE	10
template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
void ft_print_map( ft::map<Key, T> & ft_map)
{
	ft::map<std::string, int>::const_iterator it = ft_map.begin();
	for (; it != ft_map.end(); ++it)
		std::cout << it->first << ": " << it->second << " ";
	std::cout << std::endl;
}

int main(void) {
	ft::map<std::string, int>						ft_map;
	ft::map<std::string, int>						ft_map_swap;
	ft::map<std::string, int>::iterator				it1, it2, itlow, itup;
	ft::map<std::string, int>::reverse_iterator		rev_it1, rev_it2;

	ft::map<std::string, int>::key_compare	mycomp = ft_map.key_comp();
	std::string								str;
	for (char c = 'A'; c < 'G'; ++c)
	{
		str = c;
		ft_map_swap[str] = c;
	}
	ft_map["a"] = 1;
	ft_map["b"] = 2;
	ft_map["d"] = 3;
	ft_map["c"] = 4;
	ft_map["e"] = 5;
	ft_map["t"] = 6;
	ft_map["f"] = 8;
	ft_map["g"] = 7;
	ft_print_map(ft_map);
	/* Capacity ---------------------------------------------------------------------- */
	std::cout << FPURPLE;
	std::cout.fill('-');
	std::cout.width(100);
	std::cout << std::left << "Capacity "<< NONE << std::endl;

	if (!ft_map.empty())
		std::cout << "Map is not empty!" << std::endl;
	else
		std::cout << "Map is empty!" << std::endl;
	std::cout << "Size: " << ft_map.size() << std::endl;
	std::cout << "Max_size: " << ft_map.max_size() << std::endl;

	/* Element access ---------------------------------------------------------------------- */	
	std::cout << FPURPLE;
	std::cout.fill('-');
	std::cout.width(100);
	std::cout << std::left << "Element access "<< NONE << std::endl;
	std::cout << "Change map[a] value (new val - 10)" << std::endl;
	ft_map["a"] = 10;
	ft_print_map(ft_map);
	std::cout << "Access invalid key with at" << std::endl;
	try
	{
		ft_map.at("lol") = 20;
	}
	catch(const std::exception& e)
	{
		std::cerr << FRED << e.what() << NONE << '\n';
	}
	std::cout << "Change map value using at" << std::endl;
	ft_map.at("b") = 10;
	ft_print_map(ft_map);
	
	/* Modifiers  ---------------------------------------------------------------------- */	
	std::cout << FPURPLE;
	std::cout.fill('-');
	std::cout.width(100);
	std::cout << std::left << "Modifiers "<< NONE << std::endl;
	ft_map.insert(ft::pair<std::string, int>("k", 100));
	std::cout << "Remove map[c]" << std::endl;
	it1 = ft_map.find("c");
	ft_map.erase(it1);
	ft_print_map(ft_map);
	std::cout << "Remove map[e] - map[g]" << std::endl;
	it1 = ft_map.find("e");
	printf("Found e\n");
	it2 = ft_map.find("g");
	printf("Found g\n");
	ft_map.erase(it1, it2);
	ft_print_map(ft_map);
	std::cout << "Swap maps" << std::endl;
	ft_map_swap.swap(ft_map);
	ft_map["W"] = -1;
	ft_map["G"] = 100;
	ft_print_map(ft_map);
	std::cout << "Reverse iterator" << std::endl;
	rev_it1 = ft_map.rbegin();
	// std::cout << rev_it1->first << " => " << rev_it1->second << "; "  << std::endl;;
	*rev_it1++;
	std::cout << rev_it1->first << " => " << rev_it1->second << "; "  << std::endl;;
	*rev_it1++;
	std::cout << rev_it1->first << " => " << rev_it1->second << "; "  << std::endl;;
	(*--rev_it1);
	std::cout << rev_it1->first << " => " << rev_it1->second << "; "  << std::endl;;

	/* Observers  ---------------------------------------------------------------------- */	
	std::cout << FPURPLE;
	std::cout.fill('-');
	std::cout.width(100);
	std::cout << std::left << "Observers "<< NONE << std::endl;
	it1 = ft_map.begin();
	it2 = ft_map.end();
	it2--;
	it2--;
	it2--;
	std::cout << "(key_compare test) Print all values with key less than " << it2->second << std::endl;
	while (mycomp((*it1).first, it2->first))
	{
		std::cout << it1->first << " => " << it1->second << "; ";
		*it1++;
	}
	std::cout << std::endl;
	
	it1 = ft_map.begin();
	it2 = ft_map.end();
	it1++;
	it1++;
	// it2--;
	// std::cout << "(key_compare test) Print all values with key from " << it1->second << " and less than " << it2->second << std::endl;
	// while (ft_map.value_comp()(*it1, *it2)) {
	// 	std::cout << it1->first << " => " << it1->second << "; ";
	// 	*it1++;
	// }
	// std::cout << std::endl;

	/* Operations  ---------------------------------------------------------------------- */	
	std::cout << FPURPLE;
	std::cout.fill('-');
	std::cout.width(100);
	std::cout << std::left << "Operations "<< NONE << std::endl;
	
	std::cout << "(test for find) ft_map[W]: " << ft_map.find("W")->second << std::endl;

	for (char ch = 'F'; ch < 'I'; ++ch)
	{
		str = ch;
		if (ft_map.count(str) > 0)
			std::cout << "(test for count) " << str << " key is in my map" << std::endl;
		else
			std::cout << "(test for count) " << str << " key is NOT in my map" << std::endl;
	}

	itlow = ft_map.lower_bound("B");
	itup = ft_map.upper_bound("B");
	std::cout << "(test for lower_bound) key: " << itlow->first << " value: " << itlow->second << std::endl;
	std::cout << "(test for upper_bound) key: " << itup->first << " value: " << itup->second << std::endl;
  	ft::pair<ft::map<std::string,int>::iterator,ft::map<std::string,int>::iterator> ret;
	ret = ft_map.equal_range("B");
	std::cout << "(test for equal_range) lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';
	std::cout << "(test for equal_range) upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';


	return (0);
}