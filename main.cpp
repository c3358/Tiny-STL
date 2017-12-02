#include <iostream>

#include "IK_Algorithm.h"
#include "IK_Vector.h"
#include "IK_List.h"
#include "IK_Deque.h"
#include "IK_RB_Tree.h"
#include "IK_Set.h"
#include "IK_Map.h"

int main()
{
	IK_STL::vector<int>test_vec;
	
	int arr[5] = { 3,2,434,534,1 };
	for (int i = 0; i < 5; i++)
		test_vec.push_back(arr[i]);

	IK_STL::make_heap(test_vec.begin(),test_vec.end());
	IK_STL::sort_heap(test_vec.begin(), test_vec.end());
	for (auto ite = test_vec.begin(); ite < test_vec.end(); ++ite)
		std::cout << *ite<<" ";
	//IK_STL::list<int>test_list;
	//int arr[5] = { 3,2,434,534,1 };
	//for (int i = 0; i < 5; i++)
	//	test_list.push_back(arr[i]);
	//test_list.sort();
	//IK_STL::LI_ITER::listIterator<int> ite = test_list.begin();
	//for (; ite != test_list.end(); ++ite)
	//{
	//	std::cout << *ite<<" ";
	//}
	IK_STL::deque<int>test_deque;
	IK_STL::set<int>test_set;
	



	/*std::cin.get();*/
	return 0;
}


