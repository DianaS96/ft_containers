#include <vector>
#include <chrono>
#include "vector.hpp"
#include <iomanip>
#include <ctime>
#include <stdio.h>
#include <sys/time.h>


/*fonts color*/
# define FBLACK		"\033[0;30m"
# define FRED		"\033[0;31m"
# define FGREEN		"\033[0;32m"
# define FYELLOW	"\033[0;33m"
# define FBLUE		 "\033[0;34m"
# define FPURPLE	"\033[0;35m"
# define FCYAN		"\x1b[36m"

/*end color*/
# define NONE        "\033[0m"

// using std::chrono::high_resolution_clock;
// using std::chrono::duration_cast;
// using std::chrono::duration;
// using std::chrono::milliseconds;

# define	SIZE	1000

class Timer
{
public:
	static void Start() {
		gettimeofday(&start, NULL);
	}
	static void Stop() {
		gettimeofday(&end, NULL);
		res = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
	}
	static long getRes() {
		return res;
	}
private:
	static struct timeval start;
	static struct timeval end;
	static long res;
};

struct timeval Timer::start;
struct timeval Timer::end;
long Timer::res;

struct get_data
{
	std::string	test_name;
	double	ft_time;
	double	std_time;
	double	time_dif;
	double	time_dif_perc;
};

void	ft_print_head()
{
	std::cout << std::setw(20) << "Function" << "|";
    std::cout << std::setw(27) << "Size and capacity" << "|";
    std::cout << std::setw(37) << "Values in underlaying array" << "|";
    std::cout << std::setw(20) << "Time (ft namespace), ms" << "|";
    std::cout << std::setw(20) << "Time (std namespace), ms" << "|";
    std::cout << std::setw(13) << "Diff, ms" << "|";
    std::cout << std::setw(20) << "Diff, %" << std::endl;
}

template<typename T>
int	ft_check_values(ft::vector<T> ft_vec, std::vector<T> std_vec)
{
	for (size_t i = 0; i < ft_vec.size(); ++i)
		if (ft_vec[i] != std_vec[i])
			return 1;
	return 0;
}

template<typename T>
void	ft_print_stats(ft::vector<T> ft_vec, std::vector<T> std_vec, get_data data)
{
	const char	*color = FGREEN;
	if (data.time_dif_perc > 2000)
		color = FRED;
	std::cout << "size_ft: " << ft_vec.size() << ", size_std: " << std_vec.size() << std::endl;
	std::cout << "cap_ft: " << ft_vec.capacity() << ", cap_std: " << std_vec.capacity() << std::endl;

	std::cout.precision(5);
	std::cout << std::setw(20) << data.test_name << "|";
	if (std_vec.size() != ft_vec.size() || std_vec.capacity() != ft_vec.capacity())
   		std::cout << std::setw(10) << FRED << "Wrong size or capacity!" << NONE << "|";
	else
   		std::cout << std::setw(10) << FGREEN << "Size and capacity are ok" << NONE << "|";
	if (ft_check_values(ft_vec, std_vec))
   		std::cout << std::setw(10) << FRED << "Wrong values in underlaying array!" << NONE << "|";
	else
   		std::cout << std::setw(10) << FGREEN << "Values in underlaying array are ok" << NONE << "|";
    std::cout << std::setw(20) << std::fixed << data.ft_time << " ms" << "|";
    std::cout << std::setw(21) << data.std_time << " ms" << "|";
    std::cout << std::setw(10) << data.time_dif << " ms" << "|";
    std::cout << std::setw(20) << color << data.time_dif_perc << " %" << NONE << std::endl;
	
}

void	ft_fill_data(std::string test_name, double &ms_double_ft, double &ms_double_std, get_data &data)
{
	data.test_name = test_name;
	data.ft_time = ms_double_ft;
	data.std_time = ms_double_std;
	data.time_dif = data.ft_time - data.std_time;
	data.time_dif_perc = (data.time_dif / data.std_time) * 100;	
}

template<typename T>
void	ft_push_back(ft::vector<T> &ft_vec)
{
	for (size_t i = 0; i < SIZE; ++i)
	{
		ft_vec.push_back(1);
	}
}

template<typename T>
void	std_push_back(std::vector<T> &std_vec)
{
	for (size_t i = 0; i < SIZE; ++i)
	{
		std_vec.push_back(1);
	}
}

int main(void) {
	std::cout << "--------------------------------------- VECTOR TEST ---------------------------------------" << std::endl;
	get_data data;
	ft::vector<int> ft_vec;
	std::vector<int> std_vec;
	ft::vector<int> tmp_ft;
	std::vector<int> tmp_std;
  	// time_t begin, end;
	double ms_double_ft, ms_double_std;
	for (size_t i = 0; i < 20; ++i)
	{
		tmp_ft.push_back(i);
		tmp_std.push_back(i);
	}
	ft_print_head();
	/*------------------------ push_back ------------------------*/
	
	Timer::Start();
	ft_push_back(ft_vec);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_push_back(std_vec);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	printf("%f, %f\n", ms_double_ft, ms_double_std);

	ft_fill_data("push_back", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data);
	/*------------------------ assign (count, value) ------------------------*/
	Timer::Start();
	ft_vec.assign(6, 4);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.assign(6, 4);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("assign (count, val)", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data);
	/*------------------------ assign (it, it) ------------------------*/
	Timer::Start();
	ft_vec.assign(tmp_ft.begin(), tmp_ft.end());
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.assign(tmp_std.begin(), tmp_std.end());
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("assign (it, it)", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data);

	return (0);
}