#pragma once
#include "BS_Tree.cpp"
enum DEEP_DIRECTION { L = 0, R = 1 };
//enum HIGH_DIRECTINO { L = 0, R = 2 };
enum ROTATE_DIRECTION { LL = 0, LR = 1, RL = 2, RR = 3 };

template<typename T>
struct AVL_Node:public Node<T>{    //��:
	int height;   //�ڵ�ǿո߶ȼ�1
	AVL_Node<T>* left;
	AVL_Node<T>* right;
	/*T data;*/
	AVL_Node(T data_, AVL_Node<T>* left_, AVL_Node<T>* right_,int height_):Node(data_), left(left_), right(right_),height(height_) {}
};

template<typename T>
class AVL_Tree :
	public BS_Tree<T>
{
public:
	void show_tree()const;          //������չʾ�߶�
	void insert_node(const T &value); //��дinsert insert�иı���˸��ı�߶Ⱥ���ת
	void test();
	AVL_Node<T> *root;
	AVL_Tree();
	~AVL_Tree();
private:
	void _single_rotate(AVL_Node<T>*&father_node, AVL_Node<T>*&son_node, DEEP_DIRECTION _dir);
	void _double_rotate(AVL_Node<T>**father_node, AVL_Node<T>**son_node, DEEP_DIRECTION _first_dir);

	void _is_balance(stack<pair<AVL_Node<T>**, DEEP_DIRECTION>> &src);   //����·��
	inline int tree_height(AVL_Node<T> *_node)const;
	
	void _fix(AVL_Node<T>**father_node, AVL_Node<T>**son_node, ROTATE_DIRECTION _dir);
	
};


