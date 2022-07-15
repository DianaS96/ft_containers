#include <vector>
#include "containers/vector.hpp"

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
    std::cout << std::setw(28) << SIZE_CAP_HEADER << "|";
    std::cout << std::setw(37) << "Values in underlaying array" << "|";
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

template<typename T>
void	ft_print_stats(ft::vector<T> &ft_vec, std::vector<T> &std_vec, get_data data, int res)
{
	const char	*color = FGREEN;

	// std::cout << "ft_s: " << ft_vec.size() << " ft_cap: " << ft_vec.capacity() << std::endl;
	// std::cout << "_s: " << std_vec.size() << " std_cap: " << std_vec.capacity() << std::endl;
	// std::cout << "back: " << ft_vec.back() << std::endl;

	if (data.time_dif_perc > 2000)
		color = FRED;
	std::cout.precision(5);
	std::cout << std::setw(20) << data.test_name << "|";
	if (std_vec.size() != ft_vec.size() || std_vec.capacity() != ft_vec.capacity())
   		std::cout << std::setw(35 - std::string(WRONG_SIZE_CAP).length()) << FRED << WRONG_SIZE_CAP << NONE << "|";
	else
   		std::cout << std::setw(35 - std::string(SIZE_CAP_OK).length()) << FGREEN << SIZE_CAP_OK << NONE << "|";
	if (ft_check_values(ft_vec, std_vec))
   		std::cout << std::setw(10) << FRED << "Wrong values in underlaying array!" << NONE << "|";
	else
   		std::cout << std::setw(10) << FGREEN << "Values in underlaying array are ok" << NONE << "|";
	if (res == 0)
		std::cout << std::setw(15) << FGREEN << "N/A" << NONE << "|";
	else if (res == 1)
		std::cout << std::setw(15) << FGREEN << " Ok" << NONE << "|";
	if (res == 2)
		std::cout << std::setw(15) << FRED << " =(" << NONE << "|";
    std::cout << std::setw(20) << std::fixed << data.ft_time << " ms" << "|";
    std::cout << std::setw(21) << data.std_time << " ms" << "|";
    std::cout << std::setw(10) << data.time_dif << " ms" << "|";
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

void	ft_push_back_test(double ms_double_ft, double ms_double_std, get_data &data, \
ft::vector<int> &ft_vec, std::vector<int> &std_vec)
{
	Timer::Start();
	ft_push_back(ft_vec);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_push_back(std_vec);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("push_back", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, NO_RETURN_VALUE);
}

void	ft_assign_test(double ms_double_ft, double ms_double_std, get_data &data, \
ft::vector<int> &ft_vec, std::vector<int> &std_vec)
{
	Timer::Start();
	ft_vec.assign(6, 4);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.assign(6, 4);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("assign (count, val)", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, NO_RETURN_VALUE);
}

void	ft_assign_it_test(double ms_double_ft, double ms_double_std, get_data &data, \
ft::vector<int> &ft_vec, std::vector<int> &std_vec, ft::vector<int> &tmp_ft, std::vector<int> &tmp_std)
{
	Timer::Start();
	ft_vec.assign(tmp_ft.begin(), tmp_ft.end());
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.assign(tmp_std.begin(), tmp_std.end());
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("assign (it, it)", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, NO_RETURN_VALUE);
}

template <typename T1>
void	ft_at_test(double ms_double_ft, double ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int	res = BAD_RETURN_VALUE;
	typename std::vector<T1>::value_type	std_return;
	typename ft::vector<T1>::value_type		ft_return;

	Timer::Start();
	ft_return = ft_vec.at(0);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_return = std_vec.at(0);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	if (ft_return == std_return)
	 	res = OK_RETURN_VALUE;
	ft_fill_data("at", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_brackets_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int	res = BAD_RETURN_VALUE;
	typename std::vector<T1>::value_type	std_return;
	typename ft::vector<T1>::value_type		ft_return;

	Timer::Start();
	ft_return = ft_vec[4];
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_return = std_vec[4];
	Timer::Stop();
	ms_double_std = Timer::getRes();
	if (ft_return == std_return)
	 	res = OK_RETURN_VALUE;
	ft_fill_data("operator[]", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_front_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int	res = BAD_RETURN_VALUE;
	typename std::vector<T1>::value_type	std_return;
	typename ft::vector<T1>::value_type		ft_return;

	Timer::Start();
	ft_return = ft_vec.front();
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_return = std_vec.front();
	Timer::Stop();
	ms_double_std = Timer::getRes();
	if (ft_return == std_return)
	 	res = OK_RETURN_VALUE;
	ft_fill_data("front", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_back_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int	res = BAD_RETURN_VALUE;
	typename std::vector<T1>::value_type	std_return;
	typename ft::vector<T1>::value_type		ft_return;

	Timer::Start();
	ft_return = ft_vec.back();
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_return = std_vec.back();
	Timer::Stop();
	ms_double_std = Timer::getRes();
	if (ft_return == std_return)
	 	res = OK_RETURN_VALUE;
	ft_fill_data("back", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_data_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int	res = OK_RETURN_VALUE;
	typename std::vector<T1>::value_type	*std_return;
	typename ft::vector<T1>::value_type		*ft_return;

	Timer::Start();
	ft_return = ft_vec.data();
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_return = std_vec.data();
	Timer::Stop();
	ms_double_std = Timer::getRes();
	for (size_t i = 0; i < ft_vec.size(); ++i)
	{
		if (ft_return[i] != std_return[i])
		{
			res = BAD_RETURN_VALUE;
			break;
		}
	}
	ft_fill_data("data", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_empty_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int		res = OK_RETURN_VALUE;
	bool	std_return;
	bool	ft_return;

	Timer::Start();
	ft_return = ft_vec.empty();
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_return = std_vec.empty();
	Timer::Stop();
	ms_double_std = Timer::getRes();
	if (std_return != ft_return)
		res = BAD_RETURN_VALUE;
	ft_fill_data("empty", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_size_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int		res = OK_RETURN_VALUE;
	size_t	std_return;
	size_t	ft_return;

	Timer::Start();
	ft_return = ft_vec.size();
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_return = std_vec.size();
	Timer::Stop();
	ms_double_std = Timer::getRes();
	if (std_return != ft_return)
		res = BAD_RETURN_VALUE;
	ft_fill_data("size", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_max_size_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int		res = OK_RETURN_VALUE;
	size_t	std_return;
	size_t	ft_return;

	Timer::Start();
	ft_return = ft_vec.max_size();
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_return = std_vec.max_size();
	Timer::Stop();
	ms_double_std = Timer::getRes();
	if (std_return != ft_return)
		res = BAD_RETURN_VALUE;
	ft_fill_data("max_size", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_capacity_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int		res = OK_RETURN_VALUE;
	size_t	std_return;
	size_t	ft_return;

	Timer::Start();
	ft_return = ft_vec.capacity();
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_return = std_vec.capacity();
	Timer::Stop();
	ms_double_std = Timer::getRes();
	if (std_return != ft_return)
		res = BAD_RETURN_VALUE;
	ft_fill_data("capacity", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_reserve_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int		res = 0;

	Timer::Start();
	ft_vec.reserve(ft_vec.capacity() * 2);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.reserve(std_vec.capacity() * 2);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("reserve", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_insert_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int res								= 0;
	int val								= -1;
	typename ft::vector<T1>::iterator	ft_it = ft_vec.begin();
	typename std::vector<T1>::iterator	std_it = std_vec.begin();

	ft_it++;
	std_it++;
	Timer::Start();
	ft_vec.insert(ft_it, val);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.insert(std_it, val);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("insert", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_insert_count_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int res								= 0;
	int count							= 30;
	int val								= -40;
	typename ft::vector<T1>::iterator	ft_it = ft_vec.begin();
	typename std::vector<T1>::iterator	std_it = std_vec.begin();

	ft_it++;
	std_it++;
	Timer::Start();
	ft_vec.insert(ft_it, count, val);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.insert(std_it, count, val);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("insert_count", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_insert_iter_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec, ft::vector<T1> &ft_tmp, std::vector<T1> &std_tmp)
{
	int res								= 0;
	typename ft::vector<T1>::iterator	ft_it = ft_vec.begin();
	typename std::vector<T1>::iterator	std_it = std_vec.begin();

	ft_it++;
	std_it++;
	Timer::Start();
	ft_vec.insert(ft_it, ft_tmp.begin(), ft_tmp.end());
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.insert(std_it, std_tmp.begin(), std_tmp.end());
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("insert_iter", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_erase_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int res								= 0;
	typename ft::vector<T1>::iterator	ft_it = ft_vec.begin();
	typename std::vector<T1>::iterator	std_it = std_vec.begin();

	ft_it += ft_vec.size() / 2;
	std_it += std_vec.size() / 2;
	Timer::Start();
	ft_vec.erase(ft_it);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.erase(std_it);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("erase", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_erase_iter_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int res								= 0;
	typename ft::vector<T1>::iterator	ft_it = ft_vec.begin();
	typename std::vector<T1>::iterator	std_it = std_vec.begin();

	ft_it += ft_vec.size() / 2;
	std_it += std_vec.size() / 2;
	Timer::Start();
	ft_vec.erase(ft_vec.begin(), ft_it);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.erase(std_vec.begin(), std_it);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("erase_iter", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_pop_back_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int res								= 0;

	Timer::Start();
	ft_vec.pop_back();
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.pop_back();
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("pop_back", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_resize_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int	res = 0;
	int	count = ft_vec.size() / 2;
	int	value = 100;

	Timer::Start();
	ft_vec.resize(count, value);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.resize(count, value);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("resize (increase)", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_resize2_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec)
{
	int	res = 0;
	int	count = ft_vec.size() * 2;
	int	value = 100;

	Timer::Start();
	ft_vec.resize(count, value);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.resize(count, value);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("resize (decrease)", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

template <typename T1>
void	ft_swap_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec, ft::vector<T1> &ft_tmp, std::vector<T1> &std_tmp)
{
	int	res = 0;

	Timer::Start();
	ft_vec.swap(ft_tmp);
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.swap(std_tmp);
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("swap", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}

/*template <typename T1>
void	ft_erase_iter_test(double &ms_double_ft, double &ms_double_std, get_data &data, \
ft::vector<T1> &ft_vec, std::vector<T1> &std_vec, ft::vector<T1> &ft_tmp, std::vector<T1> &std_tmp)
{
	int res								= 0;
	typename ft::vector<T1>::iterator	ft_it = ft_vec.begin();
	typename std::vector<T1>::iterator	std_it = std_vec.begin();

	ft_it++;
	std_it++;
	Timer::Start();
	ft_vec.insert(ft_it, ft_tmp.begin(), ft_tmp.end());
	Timer::Stop();
	ms_double_ft = Timer::getRes();
	Timer::Start();
	std_vec.insert(std_it, std_tmp.begin(), std_tmp.end());
	Timer::Stop();
	ms_double_std = Timer::getRes();
	ft_fill_data("insert_iter", ms_double_ft, ms_double_std, data);
	ft_print_stats(ft_vec, std_vec, data, res);
}*/

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
	data.ft_total_time = 0;
	data.std_total_time = 0;
	ft_print_head();
	/*------------------------ push_back ------------------------*/
	ft_push_back_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	/*------------------------ assign (count, value) ------------------------*/
	ft_assign_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	/*------------------------ assign (it, it) ------------------------*/
	ft_assign_it_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec, tmp_ft, tmp_std);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;

	std::cout << "Elements access --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	/*------------------------ at ------------------------*/
	ft_at_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	/*------------------------ operator[] ------------------------*/
	ft_brackets_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	/*------------------------ front ------------------------*/
	ft_front_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	/*------------------------ back ------------------------*/
	ft_back_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	/*------------------------ data ------------------------*/
	ft_data_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;

	std::cout << "Capacity ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	/*------------------------ empty ------------------------*/
	ft_empty_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;

	/*------------------------ size ------------------------*/
	ft_size_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;

	/*------------------------ max_size ------------------------*/
	ft_max_size_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;

	/*------------------------ capacity ------------------------*/
	ft_capacity_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;

	/*------------------------ reserve ------------------------*/
	ft_reserve_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;
	// for (size_t i = 0; i < ft_vec.size(); ++i)
	// {
	// 	std::cout << "ft: " << ft_vec[i] << "; std:: " << std_vec[i] << std::endl;
	// }
	std::cout << "Modifiers --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	/*------------------------ insert ------------------------*/
	ft_insert_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;
	
	/*------------------------ insert (with count option) ------------------------*/
	ft_insert_count_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;
	ft_insert_count_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;
	
	/*------------------------ insert (with iterators) ------------------------*/
	ft_insert_iter_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec, tmp_ft, tmp_std);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;
	ft_insert_iter_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec, tmp_ft, tmp_std);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;
	ft_insert_iter_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec, tmp_ft, tmp_std);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;
	ft_insert_iter_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec, tmp_ft, tmp_std);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;
	ft_insert_iter_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec, tmp_ft, tmp_std);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;
	ft_insert_iter_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec, tmp_ft, tmp_std);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;
	ft_insert_iter_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec, tmp_ft, tmp_std);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;
	ft_insert_iter_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec, tmp_ft, tmp_std);
	data.ft_total_time += data.ft_time;
	data.std_total_time += data.std_time;
	// std::cout << ft_vec.capacity() << ", " << ft_vec.size() << std::endl;
	// std::cout << std_vec.capacity() << ", " << std_vec.size()  << std::endl;

	/*------------------------ erase ------------------------*/
	ft_erase_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);

	/*------------------------ erase (with iterators) ------------------------*/
	ft_erase_iter_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);

	/*------------------------ pop_back ------------------------*/
	ft_pop_back_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);

	/*------------------------ resize ------------------------*/
	ft_resize_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	ft_resize2_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec);
	// for (size_t i = 0; i < ft_vec.size(); ++i)
	// 	std::cout << ft_vec[i] << std::endl;

	/*------------------------ swap ------------------------*/
	ft_swap_test(ms_double_ft, ms_double_std, data, ft_vec, std_vec, tmp_ft, tmp_std);
	// for (size_t i = 0; i < ft_vec.size(); ++i)
	// 	std::cout << ft_vec[i] << std::endl;

	std::cout << "ft_total_time: " << data.ft_total_time << " std_total_time: " << data.std_total_time << std::endl;
	std::cout << "Diff, ms: " << data.ft_total_time - data.std_total_time << std::endl;
	std::cout << "Diff, %: " << (data.ft_total_time - data.std_total_time) / data.std_total_time << std::endl;

	return (0);
}