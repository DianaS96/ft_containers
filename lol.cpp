#include "vector.hpp"
#include <iostream>

int main(void)
{
    ft::vector<int> vector_int;
    vector_int.push_back(1);
    std:: cout << vector_int[0] << std::endl;
    vector_int.push_back(2);
    std:: cout << vector_int[1] << std::endl;
}

