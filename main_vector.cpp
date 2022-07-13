#include <vector>
#include <chrono>
#include "vector.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

# define	SIZE	10000

struct get_data
{
	std::string	test_name;
	double	ft_time;
	double	std_time;
	double	time_dif;
	double	time_dif_perc;
};


void	ft_push_back(ft::vector<int> ft_vec)
{
	for (size_t i = 0; i < SIZE; ++i)
	{
		ft_vec.push_back(1);
	}
}

void	std_push_back(std::vector<int> std_vec)
{
	for (size_t i = 0; i < SIZE; ++i)
	{
		std_vec.push_back(1);
	}
}

int main(void) {
	std::cout << "------------- VECTOR TEST -------------" << std::endl;
	get_data data;
	ft::vector<int> ft_vec;
	std::vector<int> std_vec;
	
	auto t1 = high_resolution_clock::now();
	ft_push_back(ft_vec);
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
	data.ft_time = ms_double.count();
	
	t1 = high_resolution_clock::now();
	std_push_back(std_vec);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
	data.test_name = "push_back";
	data.std_time = ms_double.count();
	data.time_dif = data.ft_time - data.std_time;
	data.time_dif_perc = (data.time_dif / data.std_time) * 100;
	// std::cout 
    std::cout << data.test_name << "\n";
    std::cout << data.ft_time << " ms\n";
    std::cout << data.std_time << " ms\n";
    std::cout << data.time_dif << " ms\n";
    std::cout << data.time_dif_perc << " %\n";
	return (0);
}