#include "../test_utility_map.cpp"

#define	TEST 0
#define	LEAK 0

int	test(int size, string test)
{
	string					temp_orig = "", temp_my = "", num_str = "";
	unsigned int			time_orig = 0, time_my = 0, rez = 0;
	std::map<int, string>	orig;
	ft::map<int, string>	my;

	for (int i = 0; i < size; i++)
	{
		num_str = to_string(i) + "_";
		orig.insert(std::pair<int, string>(i, num_str));
		my.insert(ft::pair<int, string>(i, num_str));
	}

	std::map<int, string> const orig_const(orig);
	ft::map<int, string> const my_const(my);

	cout << test << endl;
	//===========================ORIG==============================
	time_orig = clock();
	for (int i = 0; i < size; i++)
		temp_orig += orig_const.find(i)->second;
	time_orig = clock() - time_orig;
	//============================MY===============================
	time_my = clock();
	for (int i = 0; i < size; i++)
		temp_my += my_const.find(i)->second;
	if (TEST)
		temp_my += " ";
	time_my = clock() - time_my;
	//=============================================================
	rez += print_status_comp(temp_orig, temp_my);
	rez += print_status_time(time_orig, time_my);
	return (rez);
}

int	main()
{
	string	str_leaks = "";
	int		rez = 0;

	//=============================================================
	rez += test(SIZE_1, "Test 1/4");
	rez += test(SIZE_100, "Test 2/4");
	rez += test(SIZE_10K, "Test 3/4");
	rez += test(SIZE_100K, "Test 4/4");
	//rez += test(SIZE_1M, "Test 5");
	//=============================================================
	if (LEAK)
		cin >> str_leaks;
	return (!rez);
}
