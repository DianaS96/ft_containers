#include <map>
#include "containers/map.hpp"

template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
void ft_print_map( ft::map<Key, T> & ft_map)
{
	ft::map<std::string, int>::const_iterator it = ft_map.begin();
	for (; it != ft_map.end(); ++it)
		std::cout << it->first << ": " << it->second << " ";
	std::cout << std::endl;
}

int main(void) {
	ft::map<std::string, int>				ft_map;
	ft::map<std::string, int>				ft_map_swap;
	ft::map<std::string, int>::iterator		it1;
	ft::map<std::string, int>::iterator		it2;
	ft::map<std::string, int>::key_compare	mycomp = ft_map.key_comp();
	std::string							str;
	printf("Hi again!\n");
	for (char c = 'A'; c < 'G'; ++c)
	{
		printf("Hi again!\n");
		str = c;
		ft_map_swap[str] = c;
	}
	printf("Hi again!\n");
	ft_map["a"] = 1;
	printf("Hi again!\n");
	ft_map["b"] = 2;
	ft_map["d"] = 3;
	ft_map["c"] = 4;
	ft_map["e"] = 5;
	ft_map["t"] = 6;
	printf("Hi again!\n");
	ft_map["f"] = 8;
	printf("Hi again!\n");
	ft_map["g"] = 7;
	printf("Hi again!\n");
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
	ft_map["Z"] = -1;
	ft_map["G"] = 100;
	ft_print_map(ft_map);

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
	it2--;
	std::cout << "(key_compare test) Print all values with key from " << it1->second << " and less than " << it2->second << std::endl;
	while (ft_map.value_comp()(*it1, *it2)) {
		std::cout << it1->first << " => " << it1->second << "; ";
		*it1++;
	}
	std::cout << std::endl;

	/* Operations  ---------------------------------------------------------------------- */	
	std::cout << FPURPLE;
	std::cout.fill('-');
	std::cout.width(100);
	std::cout << std::left << "Operations "<< NONE << std::endl;

	return (0);
}