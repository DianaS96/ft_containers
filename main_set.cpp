#include <iostream>
// namespace ft = std;
// #include <set>
#include "containers/set.hpp"
#include "src/utils2.hpp"


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

template< class Key, class Compare, class Allocator >
void ft_print_map( ft::set<Key, Compare, Allocator> & ft_set)
{
	ft::set<int>::const_iterator it = ft_set.begin();
	for (; it != ft_set.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int main(void) {
	Timer::Start();
	ft::set<int>							ft_set;
	ft::set<int>							ft_set_swap;
	ft::set<int>::iterator					it1, it2, itlow, itup;
	ft::set<int>::reverse_iterator			rev_it1, rev_it2;
	ft::set<int>::const_reverse_iterator	const_rev_it1, const_rev_it2;

	ft::set<int>::key_compare	mycomp = ft_set.key_comp();
	for (int i = 0; i < 20; ++i)
		ft_set_swap.insert(i * i);
	for (int i = 0; i < 10; ++i)
		ft_set.insert(i);
	ft_print_map(ft_set);
	/* Capacity ---------------------------------------------------------------------- */
	std::cout << FPURPLE;
	std::cout.fill('-');
	std::cout.width(100);
	std::cout << std::left << "Capacity "<< NONE << std::endl;

	if (!ft_set.empty())
		std::cout << "Set is not empty!" << std::endl;
	else
		std::cout << "Set is empty!" << std::endl;
	std::cout << "Size: " << ft_set.size() << std::endl;
	std::cout << "Max_size: " << ft_set.max_size() << std::endl;

	/* Modifiers  ---------------------------------------------------------------------- */	
	std::cout << FPURPLE;
	std::cout.fill('-');
	std::cout.width(100);
	std::cout << std::left << "Modifiers "<< NONE << std::endl;
	std::cout << "Remove set with key 7" << std::endl;
	it1 = ft_set.find(7);
	ft_set.erase(it1);
	ft_print_map(ft_set);
	std::cout << "Remove set with elements b/w 3 and 5" << std::endl;
	it1 = ft_set.find(3);
	printf("Found 3\n");
	it2 = ft_set.find(5);
	printf("Found 5\n");
	ft_set.erase(it1, it2);
	ft_print_map(ft_set);
	std::cout << "Swap sets" << std::endl;
	ft_set_swap.swap(ft_set);

	/* Observers  ---------------------------------------------------------------------- */	
	std::cout << FPURPLE;
	std::cout.fill('-');
	std::cout.width(100);
	std::cout << std::left << "Observers "<< NONE << std::endl;
	it1 = ft_set.begin();
	it2 = ft_set.end();
	it2--;
	it2--;
	it2--;
	std::cout << "(key_compare test) Print all values with key less than " << *it2 << std::endl;
	while (mycomp(*it1, *it2))
	{
		std::cout << *it1 << "; ";
		*it1++;
	}
	std::cout << std::endl;

	/* Operations  ---------------------------------------------------------------------- */	
	std::cout << FPURPLE;
	std::cout.fill('-');
	std::cout.width(100);
	std::cout << std::left << "Operations "<< NONE << std::endl;
	
	std::cout << "(test for find) ft_set with key 256: " << *ft_set.find(256) << std::endl;

	for (int i = 1; i < 10; ++i)
	{
		if (ft_set.count(i) > 0)
			std::cout << "(test for count) " << i << " key is in my set" << std::endl;
		else
			std::cout << "(test for count) " << i << " key is NOT in my set" << std::endl;
	}

	itlow = ft_set.lower_bound(6);
	itup = ft_set.upper_bound(100);
	std::cout << "(test for lower_bound) key: " << *itlow << std::endl;
	std::cout << "(test for upper_bound) key: " << *itup << std::endl;
  	ft::pair<ft::set<int>::iterator,ft::set<int>::iterator> ret;
	ret = ft_set.equal_range(255);
	std::cout << "(test for equal_range) lower bound points to: ";
	std::cout << *ret.first << '\n';
	std::cout << "(test for equal_range) upper bound points to: ";
	std::cout << *ret.second << '\n';

	/* Iterators  ---------------------------------------------------------------------- */	
	std::cout << FPURPLE;
	std::cout.fill('-');
	std::cout.width(100);
	std::cout << std::left << "Iterators "<< NONE << std::endl;

	std::cout << "Reverse iterator" << std::endl;
	rev_it1 = ft_set.rbegin();
	*rev_it1++;
	std::cout << *rev_it1 << "; " << std::endl;
	*rev_it1++;
	std::cout << *rev_it1 << "; "  << std::endl;
	std::cout << *++rev_it1 << "; "  << std::endl;
	std::cout << *rev_it1 << "; "  << std::endl;
	std::cout << *--rev_it1 << "; "  << std::endl;
	std::cout << *rev_it1 << "; "  << std::endl;

	rev_it1 = ft_set.rbegin();
	rev_it2 = ft_set.rend();
	std::cout << "Printing tree using reverse iterator" << std::endl;
	for (rev_it1 = ft_set.rbegin(); rev_it1 != rev_it2; rev_it1++)
		std::cout << *rev_it1 << std::endl;

	const_rev_it2 = ft_set.rend();
	std::cout << "Printing tree using const_reverse_iterator" << std::endl;
	for (const_rev_it1 = ft_set.rbegin(); const_rev_it1 != const_rev_it2; const_rev_it1++)
		std::cout << *const_rev_it1 << "; "  << std::endl;
	Timer::Stop();
	
	std::cout << "Total time spent: " << Timer::getRes() << std::endl;
	return (0);
}