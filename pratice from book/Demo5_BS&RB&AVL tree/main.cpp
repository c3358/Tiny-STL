//#include "BS_Tree.cpp"   //模板类不支持分离编译
#include "AVL_Tree.cpp"
#include <iostream>
int main()
{
	/*int arr[11] = { 1,2,3 ,0,9,8,7,4,6,11,5};*/
	//BS_Tree<int> BS;

	//for (int i = 0; i < 11; i++)
	//BS.insert_node(arr[i]);

	//BS.show_tree();

	/*BS.remove_node(8);
	BS.show_tree();*/

	cout << "---------------------------------------------" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "---------------------------------------------"<<endl;


	
	AVL_Tree<int>AVL;
	/*AVL.test();*/
	int arr[5] = { 1,2,3,5,4};
	for (int i = 0; i <5; i++)
		AVL.AVL_Tree::insert_node(arr[i]);

	AVL.AVL_Tree::show_tree();



	/*AVL.show_tree();*/

	/*AVL.remove_node(8);
	AVL.show_tree();*/



	std::cin.get();
	return 0;
}