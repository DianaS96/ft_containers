#include <stack>
#include "stack.hpp"
#include <vector>

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
	double	ft_total_time;
	double	std_total_time;
};

void	ft_print_head()
{
	std::cout << std::setw(20) << "Function" << "|";
    std::cout << std::setw(11) << "Return val" << "|";
    std::cout << std::setw(20) << "Time (ft namespace), ms" << "|";
    std::cout << std::setw(20) << "Time (std namespace), ms" << "|";
    std::cout << std::setw(13) << "Diff, ms" << "|";
    std::cout << std::setw(10) << "Diff, %" << std::endl;
}

template<typename T>
int	ft_check_values(ft::vector<T> ft_vec, std::vector<T> std_vec)
{
	for (size_t i = 0; i < ft_vec.size(); ++i)
		if (ft_vec[i] != std_vec[i])
			return 1;
	return 0;
}

// template<typename T>
void	ft_print_stats(get_data data, int res)
{
	const char	*color = FGREEN;

	// std::cout << "ft_s: " << ft_vec.size() << " ft_cap: " << ft_vec.capacity() << std::endl;
	// std::cout << "_s: " << std_vec.size() << " std_cap: " << std_vec.capacity() << std::endl;
	// std::cout << "back: " << ft_vec.back() << std::endl;

	if (data.time_dif_perc > 2000)
		color = FRED;
	std::cout.precision(5);
	std::cout << std::setw(20) << data.test_name << "|";
	if (res == 0)
		std::cout << std::setw(15) << FGREEN << "N/A" << NONE << "|";
	else if (res == 1)
		std::cout << std::setw(15) << FGREEN << " Ok" << NONE << "|";
	if (res == 2)
		std::cout << std::setw(15) << FRED << " =(" << NONE << "|";	
    std::cout << std::setw(20) << std::fixed << data.ft_time << " ms" << "|";
    std::cout << std::setw(21) << data.std_time << " ms" << "|";
    std::cout << std::setw(10) << data.time_dif << " ms" << "|";
	if (data.ft_time == 0.0 || data.std_time == 0.0)
	    std::cout << std::setw(10) << FGREEN << "N/A - ft_time or std_time == 0" << NONE << std::endl;
	else
	    std::cout << std::setw(10) << color << data.time_dif_perc << " %" << NONE << std::endl;
}

void	ft_fill_data(std::string test_name, double &ms_double_ft, double &ms_double_std, get_data &data)
{
	data.test_name = test_name;
	data.ft_time = ms_double_ft;
	data.std_time = ms_double_std;
	data.time_dif = data.ft_time - data.std_time;
	data.time_dif_perc = (data.time_dif / data.std_time) * 100;	
}

template < class T, class Container = ft::vector<T>, class Cont = std::vector<T> >
void	ft_top_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::stack<T, Container> &ft_stack, std::stack<T, Cont> &std_stack)
{
	int		res = BAD_RETURN_VALUE;
	size_t	ft_res;
	size_t	std_res;

	Timer::Start();
	ft_res = ft_stack.top();
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_res = std_stack.top();
	Timer::Stop();
	ms_double_std = Timer::getRes();
	if (std_res == ft_res)
		res = OK_RETURN_VALUE;
	ft_fill_data("top", ms_double_ft, ms_double_std, data);
	ft_print_stats(data, res);
}

template < class T, class Container = ft::vector<T>, class Cont = std::vector<T> >
void	ft_empty_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::stack<T, Container> &ft_stack, std::stack<T, Cont> &std_stack) {
	int		res = BAD_RETURN_VALUE;
	bool	ft_size;
	bool	std_size;

	Timer::Start();
	ft_size = ft_stack.empty();
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_size = std_stack.empty();
	Timer::Stop();
	ms_double_std = Timer::getRes();
	if (std_size == ft_size)
		res = OK_RETURN_VALUE;
	ft_fill_data("empty", ms_double_ft, ms_double_std, data);
	ft_print_stats(data, res);
}

template < class T, class Container = ft::vector<T>, class Cont = std::vector<T> >
void	ft_size_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::stack<T, Container> &ft_stack, std::stack<T, Cont> &std_stack) {
	int		res = BAD_RETURN_VALUE;
	size_t	ft_size;
	size_t	std_size;

	Timer::Start();
	ft_size = ft_stack.size();
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_size = std_stack.size();
	Timer::Stop();
	ms_double_std = Timer::getRes();
	if (std_size == ft_size)
		res = OK_RETURN_VALUE;
	ft_fill_data("size", ms_double_ft, ms_double_std, data);
	ft_print_stats(data, res);
}

template < class T, class Container = ft::vector<T>, class Cont = std::vector<T> >
void	ft_push_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::stack<T, Container> &ft_stack, std::stack<T, Cont> &std_stack) {
	int		res = 0;
	size_t	count = 100;

	Timer::Start();
	for (size_t i = 0; i < count; ++i)
		ft_stack.push(i);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	for (size_t i = 0; i < count; ++i)
		std_stack.push(i);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("push - 100", ms_double_ft, ms_double_std, data);
	ft_print_stats(data, res);
}

template < class T, class Container = ft::vector<T>, class Cont = std::vector<T> >
void	ft_pop_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::stack<T, Container> &ft_stack, std::stack<T, Cont> &std_stack) {
	int		res = 0;
	size_t	count = ft_stack.size() / 2;

	Timer::Start();
	for (size_t i = 0; i < count; ++i)
		ft_stack.pop();
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	for (size_t i = 0; i < count; ++i)
		std_stack.pop();
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("pop - size / 2", ms_double_ft, ms_double_std, data);
	ft_print_stats(data, res);
}

int main(void) {
	ft::vector<int>		ft_vec;
	std::vector<int>	std_vec;
	get_data			data;
	double 				ms_double_ft, ms_double_std;

	std::cout << FPURPLE << "-------------------------------------------------------------- STACK TEST --------------------------------------------------------------" << NONE << std::endl;
	for (size_t i = 0; i < 20; ++i)
	{
		ft_vec.push_back(i);
		std_vec.push_back(i);
	}
	
	ft_print_head();
	ft::stack<int, ft::vector<int> >		ft_stack(ft_vec);
	std::stack<int, std::vector<int> >	std_stack(std_vec);

	ft_top_test(ms_double_ft, ms_double_std, data, ft_stack, std_stack);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;

	ft_empty_test(ms_double_ft, ms_double_std, data, ft_stack, std_stack);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;

	ft_size_test(ms_double_ft, ms_double_std, data, ft_stack, std_stack);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;

	ft_push_test(ms_double_ft, ms_double_std, data, ft_stack, std_stack);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;

	ft_pop_test(ms_double_ft, ms_double_std, data, ft_stack, std_stack);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;

	ft::stack<int, ft::vector<int> >		ft_tmp(ft_stack);
	std::stack<int, std::vector<int> >	std_tmp(std_stack);

	if (ft_tmp == ft_stack)
		std::cout << "== " << "ok" << std::endl;

	if (std_tmp == std_stack)
		std::cout << "== " << "ok" << std::endl;

	std::cout << std::endl;
	std::cout << "Overall results:" << std::endl;
	std::cout << "Total time (ft_stack): " << data.ft_total_time << std::endl;
	std::cout << "Total time (std_stack) :" << data.std_total_time << std::endl;
	std::cout << "Difference, ms: " << data.std_total_time - data.ft_total_time << std::endl;
	if (data.std_total_time != 0.0 && data.ft_total_time != 0)
		std::cout << "Difference, %: " << ((data.std_total_time - data.ft_total_time) / data.std_total_time) * 100 << " %" << std::endl;

	return (0);
}