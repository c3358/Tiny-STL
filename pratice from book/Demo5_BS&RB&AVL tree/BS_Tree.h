#pragma once
#include <queue>
#include <vector>
#include<iostream> 
#include <stack>
using namespace std;


template <typename T>
struct Node
{
	T data;
	Node<T> *left;
	Node<T> *right;
	Node(T data_):data(data_){}        //??
	Node(T data_, Node<T>* left_, Node<T>* right_) :data(data_), left(left_), right(right_) {}
	~Node<T>() {  //后续遍历析构
		
		if (this->left != nullptr)
			this->left->~Node<T>();
		if (this->right != nullptr)
			this->right->~Node<T>();
		
	}
};


template <typename T>
class BS_Tree
{
	
public:
	BS_Tree() :root(nullptr) {};
	void insert_node(const T &value);
	void remove_node(const T &value);
	void show_tree()const;
	void test() ;
	Node<T>** find_node(const T &value);
	int tree_height()const { return tree_height(root); }
	int tree_height(Node<T> *_node)const;  //仅仅对于BS tree，AVL有节点有height变量
	
	//Node<T>* find_node(const T &value);
	~BS_Tree() {};  //
	
private:
	Node<T> *root;
	
	
};


//
//


