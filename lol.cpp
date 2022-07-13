    #include "vector.hpp"
    #include <iostream>
    #include <vector>
    int main(void)
    {
        // ft::vector<int> vector_int;
        // vector_int.push_back(1);
        // std::cout << vector_int[0] << std::endl;
        // // vector_int.push_back(2);
        // // std::cout << vector_int[1] << std::endl;
        // // std::cout << "front: " << vector_int.front() << std::endl;
        // // std::cout << "back: " << vector_int.back() << std::endl;
        // // ft::vector<int>::iterator it = vector_int.end();
        // // vector_int.insert(vector_int.end(), 42);
        // // std::cout << "back: " << vector_int.back() << std::endl;
        // // ft::vector<int>::iterator it1 = vector_int.begin();
        // // it1++;
        // // vector_int.insert(it1, 3);
        // // std::cout << "back: " << vector_int.back() << std::endl;
        // // std::cout << "back: " << vector_int[1] << std::endl;
        // std::cout << "----------------Insert----------------" << std::endl;
        // // ft::vector<int>::iterator it1 = vector_int.begin();
        // // it1++;
        // // vector_int.insert(it1, (size_t)3, 10);
        // // size_t i = 0;
        // // while (i < vector_int.size())
        // // {
        // //     std::cout << vector_int[i] << std::endl;
        // //     i++;
        // // }

        // ft::vector<int> vec2;
        // vec2.push_back(2);
        // vec2.push_back(3);
        // vec2.push_back(4);
        // vec2.insert(vec2.begin(), vector_int.begin(), vector_int.end());
        // size_t i = 0;
        // while (i < vec2.size())
        // {
        //     std::cout << vec2[i] << std::endl;
        //     i++;
        // }
        // std::cout << "----------------Erase----------------" << std::endl;
        // ft::vector<int>::iterator it1 = vec2.begin();
        // it1++;
        // it1++;
        // it1++;
        // it1++;
        // vec2.erase(it1, vec2.end());
        // i = 0;
        // while (i < vec2.size())
        // {
        //     std::cout << vec2[i] << std::endl;
        //     i++;
        // }
        // std::cout << "----------------std vec----------------" << std::endl;
        // std::vector<int> v;
        // v.push_back(2);
        // v.push_back(3);
        // v.push_back(4);
        // i = 0;
        // std::vector<int>::iterator it2 = v.begin();
        // it2++;
        // it2++;
        // it2++;
        // v.erase(it2, v.end());
        // while (i < v.size())
        // {
        //     std::cout << v[i] << std::endl;
        //     i++;
        // }

        ft::vector<char> ch;
        std::cout << "----------------assign1----------------" << std::endl;
        ch.assign(5, 'a');
        std::cout << ch[0] << std::endl;
        for (size_t i = 0; i < ch.size(); ++i)
            std::cout << ch[i] << std::endl;
        std::cout << "----------------assign2----------------" << std::endl;
        ch.assign(7, 'b');
        for (size_t i = 0; i < ch.size(); ++i)
            std::cout << ch[i] << std::endl;
    }

