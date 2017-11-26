#pragma once
#include "BS_Tree.cpp"

template<typename T>
struct AVL_Node :public Node<T> {
	int height;   //�ڵ�ǿո߶ȼ�1
};

template<typename T>
class AVL_Tree :
	public BS_Tree<T>
{
public:
	void insert_node(const T &value); //��дinsert insert�иı���˸��ı�߶�
	AVL_Tree();
	~AVL_Tree();
private:
	void _single_rotate(AVL_Node<T>*center, ROTATE_DIRECTION dir_);
	void _double_rotate(AVL_Node<T>*center, ROTATE_DIRECTION first_dir_);

};

