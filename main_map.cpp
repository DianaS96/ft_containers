#include <map>
#include "containers/map.hpp"

int main(void) {
    ft::map<std::string, int> ft_map;
    // ft_map.empty();
    ft_map["a"] = 1;
    ft::map<std::string, int>::iterator it;
    it = ft_map.begin();
	for (; it != ft_map.end(); ++it) {
		std::cout << it->first << ": " << it->second << ' ';
	}
    return (0);
    // std::map<std::string, int> std_map;
    // std_map["a"] = 1;
    // return (0);
}