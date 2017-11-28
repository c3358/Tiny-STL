
#include "AVL_Tree.h"

template<typename T>
AVL_Tree<T>::AVL_Tree()
{
	root = nullptr;
}
template<typename T>
AVL_Tree<T>::~AVL_Tree()
{
}
template<typename T>
void AVL_Tree<T>::test()
{
	std::cout << "what???";
}

template<typename T>
void AVL_Tree<T>::insert_node(const T &value)
{
	
	if (root == nullptr) {                         //insert root
		root = new AVL_Node<T>(value, nullptr, nullptr,1);
		return;
	}
	stack<pair<AVL_Node<T>**,DEEP_DIRECTION>> src;   //记录经过的路径，用于高度修正,提高效率但增加空间开销。
	AVL_Node<T> **cur_node = &root;
	while (true)
	{
		if (value > (*cur_node)->data) {				//>
			pair<AVL_Node<T>**, DEEP_DIRECTION> mem_for_src = make_pair(cur_node,R);
			src.push(mem_for_src);//路径入栈
			if ((*cur_node)->right) {
				cur_node = &((*cur_node)->right);
			}
			else {															//insert 右插
				AVL_Node<T>* new_node = new AVL_Node<T>(value, nullptr, nullptr,1);
				(*cur_node)->right = new_node;
				if ((*cur_node)->left == nullptr)//该节点也不存在左节点 ，那么树高度要变换
						_is_balance(src);       //回溯检查并完成修正
				return;						
			}
		}
		else {										//<
			pair<AVL_Node<T>**, DEEP_DIRECTION> mem_for_src = make_pair(cur_node, L);
			src.push(mem_for_src);
			if ((*cur_node)->left) {
				cur_node = &((*cur_node)->left);
			}
			else {
				AVL_Node<T>* new_node = new AVL_Node<T>(value, nullptr, nullptr,1);   //insert
				(*cur_node)->left = new_node;
				if ((*cur_node)->right == nullptr)
					_is_balance(src);
				return;
			}
		}
	}
	return;
}

template<typename T>
void AVL_Tree<T>::_is_balance(stack< pair<AVL_Node<T>**,DEEP_DIRECTION> > &src)
{
	if (src.size() == 1)  //当只有1个节点的路径 是一定平衡的 根节点的插入不会触发该函数 所以不能为0
	{
		((*(src.top().first))->height)++;
		src.pop();
		return;
	}
	pair<AVL_Node<T>**, DEEP_DIRECTION> father_node; //size=2;
	pair<AVL_Node<T>**, DEEP_DIRECTION> son_node;

	son_node = src.top();
	src.pop();
	father_node = src.top();
	src.pop();
	while(true)
	{  //当前循环的father节点本身高度没有改变
		if (father_node.second == L)
		{
		if (  tree_height((*(father_node.first))->left)+1<= tree_height((*(father_node.first))->right)  )//如果当前节点相应字树提高高度没有意义，也不必上溯
		return;
		else (*(father_node.first))->left->height++;
		}

		else {
			if (tree_height((*(father_node.first))->right) + 1 <= tree_height((*(father_node.first))->left))//如果当前节点相应字树提高高度没有意义，也不必上溯
				return;
			else (*(father_node.first))->right->height++;
		}
		
		if (abs(tree_height((*(father_node.first))->left) - tree_height((*(father_node.first))->right)) == 2)//
		{
			int high_direction = father_node.second;
			int deep_direction = son_node.second;
			ROTATE_DIRECTION rotate_dir_=(ROTATE_DIRECTION)(2*high_direction + deep_direction);
			//要进行旋转
			(*(father_node.first))->height++;
			int hf = (*(father_node.first))->height;
			int hs = (*(son_node.first))->height;
			
			_fix(father_node.first, son_node.first, rotate_dir_);   //_fix接受的是二级指针，由rotate具体完成原树变形
			return;
				
		}
		    if (src.empty())break;
			son_node = father_node;
			father_node = src.top();
			src.pop();
	} 


	/*((*(father_node.first))->height)++;*/
	//能到这里一定是只剩下根节点 即*father_node 等于root
	root->height = max(root->left->height, root->right->height) + 1;
}

template<typename T>
void AVL_Tree<T>::_fix(AVL_Node<T>**father_node, AVL_Node<T>**son_node, ROTATE_DIRECTION _dir)
{
	switch (_dir)
	{
	case LL:
		cout << "LL" <<" ";
		_single_rotate(*father_node, *son_node, R); //右单旋转
		break;
	case LR:
		cout << "LR" << " ";
		_double_rotate(father_node, son_node, L);   //双旋转，先右后左
		break;
	case RL:
		cout << "RL" << " ";
		_double_rotate(father_node, son_node, R);//双选转 先左后右边
		break;
	case RR:
		cout << "RR" << " ";
		_single_rotate(*father_node, *son_node, L);//左单旋转
		break;
	default:
		break;
	}
}

template<typename T>
void AVL_Tree<T>::show_tree()const
{
	

		if (root == nullptr) return;

		/*int height = root->height;*/
		//int width =100;       //模糊模拟位置(d

		int count_of_cur_nodes = 1;
		int count_of_next_nodes = 0;

		queue<AVL_Node<T>*>que_tree;
		que_tree.push(root);

		AVL_Node<T>*cur_node;
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
			std::cout << cur_node->data << "("<<cur_node->height<<")"<<" ";
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

template<typename T>
inline int AVL_Tree<T>::tree_height(AVL_Node<T> *_node)const
{
	return _node == nullptr ? 0 : _node->height;
}
template<typename T>
void AVL_Tree<T>::_single_rotate(AVL_Node<T>*&father_node, AVL_Node<T>*&son_node, DEEP_DIRECTION _dir)
{
	if (_dir == L) //左旋   //对应单旋转RR形态 RR单旋转父节点按-2处理
	{
		AVL_Node<T>*p_f=father_node;
		AVL_Node<T>*p_s = son_node;
		AVL_Node<T>*p_sl = son_node->left;

		p_f->right = p_sl;
		p_s->left = p_f;
		p_f->height=max(tree_height(p_f->left),tree_height(p_f->right))+1;//修正高度
		p_s->height= max(tree_height(p_s->left), tree_height(p_s->right)) + 1;
		father_node = p_s;
	}
	else               //右旋 //对应单旋转LL形态
	{
		AVL_Node<T>*p_f = father_node;
		AVL_Node<T>*p_s = son_node;
		AVL_Node<T>*p_sl = son_node->right;

		p_f->left = p_sl;
		p_s->right = p_f;
		p_f->height = max(tree_height(p_f->left), tree_height(p_f->right)) + 1;//修正高度
		p_s->height = max(tree_height(p_s->left), tree_height(p_s->right)) + 1;
		father_node = p_s;
	}

}

template<typename T>
void AVL_Tree<T>::_double_rotate(AVL_Node<T>**father_node, AVL_Node<T>**son_node, DEEP_DIRECTION _first_dir)
{

	if (_first_dir == R)  //先右旋 再左旋转   对应RL型
	{		
		_single_rotate(*son_node, (*son_node)->left, R);
		_single_rotate(*father_node, *son_node, L);
	}
	else  //LR
	{
		_single_rotate(*son_node, (*son_node)->right, L);
		_single_rotate(*father_node, *son_node, R);
	}
}