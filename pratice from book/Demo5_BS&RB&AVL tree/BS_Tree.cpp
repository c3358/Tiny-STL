#include "BS_Tree.h"


template <typename T>
void BS_Tree<T>::insert_node(const T &value)
{
	if (root == nullptr) {                         //insert root
		root = new Node<T>(value, nullptr, nullptr);
		return;
	}
	Node<T> *cur_node = root;
	while (true)
	{
		if (value > cur_node->data) {				//>
			if (cur_node->right) {
				cur_node = cur_node->right;
			}
			else {															//insert
				Node<T>* new_node = new Node<T>(value, nullptr, nullptr);
				cur_node->right = new_node;
				return;
			}
		}
		else {										//<
			if (cur_node->left) {
				cur_node = cur_node->left;
			}
			else {
				Node<T>* new_node = new Node<T>(value, nullptr, nullptr);   //insert
				cur_node->left = new_node;
				return;
			}
		}
	}
	return;
}
//
template <typename T>
Node<T>** BS_Tree<T>:: find_node(const T &value)  //返回真实节点
{
	if (root == nullptr)
		return nullptr;
	Node<T> **cur_node = &root;
	while(true){
		if (*cur_node == nullptr)
			return nullptr;
		if ((*cur_node)->data == value)
			return cur_node;
		if ((*cur_node)->data > value)   //找左子
			cur_node = &((*cur_node)->left);
		else cur_node = &((*cur_node)->right);//右孩子
	}
}

template<typename T>
void BS_Tree<T>::remove_node(const T &value)
{
	Node<T> **target_node=find_node(value);
	(*target_node)->~Node<T>();         //有bug
	*target_node = nullptr;
}


template <typename T>
void BS_Tree<T>::show_tree()const
{

	if (root == nullptr) return;

	int height = this->tree_height();
	//int width =100;       //模糊模拟位置(d

	int count_of_cur_nodes = 1;
	int count_of_next_nodes = 0;

	queue<Node<T>*>que_tree;
	que_tree.push(root);

	Node<T>*cur_node;
	while (!que_tree.empty())
	{
		cur_node = que_tree.front();
		que_tree.pop();

		if (cur_node->left) {    //下层加一个节点
			count_of_next_nodes++;
			que_tree.push(cur_node->left);
		}
		if (cur_node->right) {  //下层加一个节点
			count_of_next_nodes++;
			que_tree.push(cur_node->right);
		}
		std::cout << cur_node->data << ":)";
		count_of_cur_nodes--;
		if (count_of_cur_nodes == 0)
		{
			std::cout << std::endl;
			count_of_cur_nodes = count_of_next_nodes;
			count_of_next_nodes = 0;

		}
	}
	std::cout << std::endl;
}

template <typename T>
int BS_Tree<T>::tree_height(Node<T> *node)const
{
	if (node == nullptr)
	{
		return 0;
	}
	int left_height = tree_height(node->left);
	int right_height = tree_height(node->right);
	return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

template<typename T>
void BS_Tree<T>::test() {
	return;
}
