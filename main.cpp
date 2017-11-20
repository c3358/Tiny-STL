#include <iostream>

#include "IK_Algorithm.h"
#include "IK_Vector.h"
#include "IK_List.h"

int main()
{
	IK_STL::vector<int>test_vec;
	test_vec.push_back(3);

	IK_STL::list<int>test_list;
	int arr[5] = { 3,2,434,534,1 };
	for (int i = 0; i < 5; i++)
		test_list.push_back(arr[i]);
	test_list.sort();
	IK_STL::LI_ITER::listIterator<int> ite = test_list.begin();
	for (; ite != test_list.end(); ++ite)
	{
		std::cout << *ite<<" ";
	}

	std::cin.get();
	return 0;
}


