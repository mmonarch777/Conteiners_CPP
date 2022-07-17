#include "../test_utility.cpp"

int	main ()
{
	std::string			temp_orig = "", temp_my = "";
	unsigned int		time_orig = 0, time_my = 0, rez = 0;
	std::vector<int>	orig_1(SIZE_100K);
	ft::vector<int>		my_1(SIZE_100K);

	init_vector_all(&orig_1, &my_1);
	std::cout << "Test 1/3 (size = 100.000 (1 use))" << std::endl;
	time_orig = clock();
	//действия c оригиналом
	temp_orig += vektor_base_test(&orig_1);
	orig_1.pop_back();
	temp_orig += vektor_base_test(&orig_1);

	time_orig = clock() - time_orig;

	time_my = clock();
	//действия c собственной копией
	temp_my += vektor_base_test(&my_1);
	my_1.pop_back();
	temp_my += vektor_base_test(&my_1);
	//temp_my += " ";
	
	time_my = clock() - time_my;

	rez += print_status_comp(temp_orig, temp_my);
	rez += print_status_time(time_orig, time_my);
	//=============================================================
	std::cout << "Test 2/3 (size = 99.999 (50.000 use))" << std::endl;
	temp_orig = "", temp_my = "";
	time_orig = clock();
	//действия c оригиналом
	temp_orig += vektor_base_test(&orig_1);
	for (size_t i = 0; i < SIZE_50K; i++)
		orig_1.pop_back();
	temp_orig += vektor_base_test(&orig_1);

	time_orig = clock() - time_orig;

	time_my = clock();
	//действия c собственной копией
	temp_my += vektor_base_test(&my_1);
	for (size_t i = 0; i < SIZE_50K; i++)
		my_1.pop_back();
	temp_my += vektor_base_test(&my_1);
	//temp_my += " ";
	
	time_my = clock() - time_my;

	rez += print_status_comp(temp_orig, temp_my);
	rez += print_status_time(time_orig, time_my);
	//=============================================================
	std::cout << "Test 3/3 (size = 49.999 (49.999 use))" << std::endl;
	temp_orig = "", temp_my = "";
	time_orig = clock();
	//действия c оригиналом
	temp_orig += vektor_base_test(&orig_1);
	for (size_t i = 0; i < (SIZE_50K - 1); i++)
		orig_1.pop_back();
	temp_orig += vektor_base_test(&orig_1);

	time_orig = clock() - time_orig;

	time_my = clock();
	//действия c собственной копией
	temp_my += vektor_base_test(&my_1);
	for (size_t i = 0; i < (SIZE_50K - 1); i++)
		my_1.pop_back();
	temp_my += vektor_base_test(&my_1);
	//temp_my += " ";
	
	time_my = clock() - time_my;

	rez += print_status_comp(temp_orig, temp_my);
	rez += print_status_time(time_orig, time_my);

	//=============================================================
	return (!rez);
}
