//#include "BS_Tree.cpp"   //模板类不支持分离编译
#include "RB_Tree.cpp"
#include <iostream>
int main()
{

	/*BS TEST*/
	//------------------------------------------------------------
	/*int arr[11] = { 1,2,3,0,9,8,7,4,6,11,5};*/
	//BS_Tree<int> BS;

	//for (int i = 0; i < 11; i++)
	//BS.insert_node(arr[i]);

	//BS.show_tree();

	/*BS.remove_node(8);
	BS.show_tree();*/
	//------------------------------------------------------------
	/*END*/







	/*AVL TEST*/
	//------------------------------------------------------------
	//AVL_Tree<int>AVL;
	//*AVL.test();*/
	//int arr[11] = { 1,2,3,0,9,8,7,4,6,11,5};
	//int *watch_root_height;
	//int *watch_root_data;
	//for (int i = 0; i < 11; i++)
	//{ 


	//	AVL.AVL_Tree::insert_node(arr[i]);

	//	/*watch_root_height = &(AVL.root->height);
	//	watch_root_data = &(AVL.root->data);*/


	//
	//}
	//cout << "---------------------------------------------" << endl;
	//cout << "---------------------------------------------" << endl;
	//cout << "---------------------------------------------" << endl;
	//AVL.AVL_Tree::show_tree();
	//------------------------------------------------------------
	/*END*/







	int arr[11] = { 1,2,3,0,9,8,7,4,6,11,5};
	RB_Tree<int>RB;
	for (int i = 0; i < 11; i++)
	{
		RB.insert_node(arr[i]);
		cout << "------------------------------------------------"<<endl;
		cout << "------------------------------------------------"<<endl;
		cout << "--------------插入"<<arr[i]<<"----------------------------------"<<endl;
		RB.show_tree();
	}


	
	

	std::cin.get();
	return 0;
}