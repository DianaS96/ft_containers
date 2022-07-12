    #include "vector.hpp"
    #include <iostream>
    #include <vector>
    int main(void)
    {
        ft::vector<int> vector_int;
        vector_int.push_back(1);
        std::cout << vector_int[0] << std::endl;
        vector_int.push_back(2);
        std::cout << vector_int[1] << std::endl;
        std::cout << "front: " << vector_int.front() << std::endl;
        std::cout << "back: " << vector_int.back() << std::endl;
        ft::vector<int>::iterator it = vector_int.end();
        vector_int.insert(vector_int.end(), 42);
        std::cout << "back: " << vector_int.back() << std::endl;

    }

