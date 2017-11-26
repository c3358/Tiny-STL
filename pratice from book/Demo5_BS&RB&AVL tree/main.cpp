#include "BS_Tree.cpp"   //模板类不支持分离编译
#include <iostream>
int main()
{
	int arr[10] = { 1,2,3 ,0,9,8,7,4,6,11};
	BS_Tree<int> BS ;

	for (int i = 0; i < 10; i++)
		BS.insert_node(arr[i]);
	 
	 BS.show_tree();
	 
	 BS.remove_node(8);
	 BS.show_tree();
	/*test M;
	M.cc();*/


	std::cin.get();
	return 0;
}