#include <map>
#include <vector>
#include "containers/map.hpp"
#include "src/utils.hpp"
#include <unistd.h>

template <class T, class V>
std::vector<int> erase_test_3(std::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 0; i < 50 * 10000; ++i, ++j)
        mp.insert(std::make_pair(i, j));

    mp.erase(mp.begin(), --mp.end());
    v.push_back(mp.begin()->first);
    std::cout << mp.size() << std::endl;
    std::cout << v.size() << std::endl;
    std::cout << mp.begin()->first << std::endl;
    std::cout << "-------------" << std::endl;
    return v;
}

template <class T, class V>
std::vector<int> erase_test_3(ft::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 0; i < 50 * 10000; ++i, ++j)
        mp.insert(ft::make_pair(i, j));

    mp.erase(mp.begin(), --mp.end());
    v.push_back(mp.begin()->first);
    std::cout << mp.size() << std::endl;
    std::cout << v.size() << std::endl;
    std::cout << mp.begin()->first << std::endl;
    std::cout << "-------------" << std::endl;
    return v;
}

// template <class T, class V>
// std::vector<int> erase_test_1(ft::map<T, V> mp) {
//     std::vector<int> v;
//     v.push_back(mp.erase(3));
//     for (int i = 0, j = 0; i < 30; ++i, ++j)
//         mp.insert(ft::make_pair(i, j));
//     typename ft::map<T, V>::iterator it = mp.begin();
//     v.push_back(it->first);
//     v.push_back(mp.erase(-5));
//     v.push_back(mp.size());
//     v.push_back(mp.erase(0));
//     v.push_back(mp.size());
//     it = mp.begin();
//     v.push_back(it->first);
//     typename ft::map<T, V>::iterator it4 = mp.begin();
//     for (; it4 != mp.end(); it4 = mp.begin())
//         mp.erase(it4->first);
//     v.push_back(mp.erase(30 - 1));
//     v.push_back(mp.size());
//     ft::map<int, int> mp2;
//     for (int i = 0, j = 0; i < 10 ; ++i, ++j)
//         mp2.insert(ft::make_pair(i, j));
//     mp2.erase(2);
//     mp2.erase(7);
//     typename ft::map<T, V>::iterator it3 = mp2.begin();
//     for (; it3 != mp2.end(); ++it3) {
//         v.push_back(it3->first);
//         v.push_back(it3->second);
//     }
//     std::cout << "Size map_ft: " << mp2.size() << std::endl;
//     for (typename ft::map<T, V>::iterator it = mp2.begin(); it != mp2.end(); ++it)
//         std::cout << it->first << "=" << it->second << " ";
//     std::cout << std::endl;
//     for (int i = 0; i < v.size(); ++i)
//         std::cout << v[i] << " ";
//     std::cout << "mp.size: " << mp.size() << std::endl;
//     // std::cout << (mp.begin())->first << " and " << (mp.begin())->second << std::endl;
//     std::cout << "---------------------- "<< std::endl;
//     return v;
// }

int main() {
    std::map<int, int> std_map;
    ft::map<int, int> ft_map;
    // for (int i = 0; i < 20; ++i)
    // {
    //     ft_map[i] = i;
    //     std_map[i] = i;
    // }
    erase_test_3(ft_map);
    erase_test_3(std_map);  
    printf("Calling destructor2...\n");
}