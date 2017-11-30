#pragma once
#include "AVL_Tree.cpp"
typedef bool RB_COLOR;
const RB_COLOR rb_red = false;   //red 0  black 1
const RB_COLOR rb_black = true;

template<typename T>
struct RB_Node :public Node<T> {    //鉴于资料和AVL_tree parent指针能使RBtree更好的实现
	RB_COLOR color;
	RB_Node<T>*	parent;
	RB_Node<T>* left;
	RB_Node<T>* right;
	
	/*T data;*/
	RB_Node(T data_,RB_Node<T>*parent_, RB_Node<T>* left_, RB_Node<T>* right_,RB_COLOR color_) :Node(data_), parent(parent_),left(left_), right(right_), color(color_) {}
};

template <typename T>
class RB_Tree :
	public BS_Tree<T>
{
public:
	void insert_node(const T &value);
	RB_Tree();
	~RB_Tree();
	void show_tree()const;
private:
	void _is_balance(RB_Node<T>*new_node, RB_Node<T>*father_node, DEEP_DIRECTION _dir);
	void _fix(RB_Node<T>**father_node, RB_Node<T>*son_node, ROTATE_DIRECTION _dir); //有parent指针，所以不必使用二级指针
	inline RB_COLOR tree_color(RB_Node<T>*_node);
	void _single_rotate(RB_Node<T>*father_node, RB_Node<T>*son_node, DEEP_DIRECTION _dir);
	void _double_rotate(RB_Node<T>**father_node, RB_Node<T>*son_node, DEEP_DIRECTION _first_dir);
	RB_Node<T> *root;
	//RB_Node<T> *root_header;
	inline RB_Node<T>**  _get_add_from_father(RB_Node<T>*_node);

};

 