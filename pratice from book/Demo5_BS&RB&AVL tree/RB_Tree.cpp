#include "RB_Tree.h"


template<typename T>
RB_Tree<T>::RB_Tree()
{
	root = nullptr;
	//root_header = new RB_Node<T>(NULL, nullptr, root, nullptr, rb_black);
}

template<typename T>
RB_Tree<T>::~RB_Tree()
{
}

template<typename T>
void RB_Tree<T>::insert_node(const T &value)
{
	if (RB_Tree::root == nullptr) {                         //insert root
		root = new RB_Node<T>(value,nullptr, nullptr, nullptr,rb_black);  //根节点为黑色
		return;
	}
	RB_Node<T> *cur_node = root;
	while (true)
	{
		if (value>cur_node->data) {				//>
			if (cur_node->right) {
				cur_node = cur_node->right;
			}
			else {															//insert 右插
				RB_Node<T>* new_node = new RB_Node<T>(value, cur_node,nullptr, nullptr,rb_red); //为红色
				cur_node->right = new_node;
				_is_balance(new_node, cur_node, R);  
				return;
			}
		}
		else {										//insert 左插
			if (cur_node->left) {
				cur_node = cur_node->left;
			}
			else {
				RB_Node<T>* new_node = new RB_Node<T>(value,cur_node,nullptr,nullptr,rb_red);   //insert
				cur_node->left = new_node;
				_is_balance(new_node, cur_node, L);
				return;
			}
		}
	}
	return;
}

template<typename T>
void RB_Tree<T>::_is_balance(RB_Node<T>*new_node, RB_Node<T>*father_node,DEEP_DIRECTION deep_dir)
{
	if (tree_color(father_node) == rb_black)  //父亲黑色则不用修复
	{
		//cout << "父黑，结束" << endl;
		return;
	}
	else
	{
		if (father_node->parent)  //实际数据结构中 
		{
			 RB_Node<T>*uncle_node=nullptr;
			
			
			 DEEP_DIRECTION high_dir;
			//确定内外侧以及 叔节点的颜色
			 if ((father_node->parent->left) == (father_node))     //父亲为左树
			 {
				high_dir = L;										
				uncle_node = father_node->parent->right;
				 
			 }
			else if ((father_node->parent->right) == (father_node))   //父亲为右树
			{	
				high_dir = R;
				uncle_node = father_node->parent->left;
			}
			//
			 
			 if (tree_color(uncle_node) == rb_black) //对于叔黑的处理 旋转处理
			 {            
			
				 RB_Node<T>**p_grand_node_from_son = &(father_node->parent);
				 //cout <<"叔黑父红";
				 ROTATE_DIRECTION rotate_dir_ = (ROTATE_DIRECTION)(2 * high_dir + deep_dir);
				 _fix(p_grand_node_from_son, father_node, rotate_dir_);
			 }

			 else                                 //对于叔红的处理 继续上溯
			 {
				/* cout << "叔红父红";*/
				 father_node->color = rb_black;
				 uncle_node->color = rb_black;//染黑

				 if (father_node->parent->parent == nullptr)  //如果Grand是根节点
				 {  //只染叔父黑，不染红Grand
					 return;
				 }
				 else {  
					 //cout << "上溯一次" << endl;
					 father_node->parent->color = rb_red;
					 DEEP_DIRECTION grand_dir = father_node->parent->parent->left == father_node->parent ? L : R;
					 _is_balance(father_node->parent, father_node->parent->parent, grand_dir); //祖父作为红节点继续上溯
				 }
				
			 }
			//
		}
		

	}


}

template<typename T>
inline RB_COLOR RB_Tree<T>::tree_color(RB_Node<T>*_node)
{
	return (_node == nullptr) ? rb_black : _node->color;
}
template<typename T>
void RB_Tree<T>::show_tree()const
{
	if (root == nullptr) return;

	/*int height = root->height;*/
	//int width =100;       //模糊模拟位置(d

	int count_of_cur_nodes = 1;
	int count_of_next_nodes = 0;

	queue<RB_Node<T>*>que_tree;
	que_tree.push(root);

	RB_Node<T>*cur_node;
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
		std::cout << cur_node->data << "(" << ((cur_node->color)?"黑":"红")  ;
		if (cur_node->parent)
			cout << "父" << cur_node->parent->data << ")" << " ";
		else
			cout << ")" ;
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
void RB_Tree<T>::_fix(RB_Node<T>**p_father_node, RB_Node<T>*son_node, ROTATE_DIRECTION _dir)
{
	switch (_dir)
	{
	case LL:
		cout << "LL" << " ";
		_single_rotate(*p_father_node, son_node, R); 
		break;
	case LR:
		cout << "LR" << " ";
		_double_rotate(p_father_node, son_node, L);
		break;
	case RL:
		cout << "RL" << " ";
		_double_rotate(p_father_node, son_node, R);
		break;
	case RR:
		cout << "RR" << " ";
		_single_rotate(*p_father_node, son_node, L);
		break;
	default:
		cout << "something wrong";
		break;
	}
}
template<typename T>
void RB_Tree<T>::_single_rotate(RB_Node<T>*father_node, RB_Node<T>*son_node, DEEP_DIRECTION _dir)  //其接受的第一个参数为子节点的parent指针&，父节点对应指针在函数内计算
{
	if (_dir == L)  //RR
	{
		RB_Node<T>*p_f = father_node;
		RB_Node<T>**p_f_from_f = _get_add_from_father(father_node);
		RB_Node<T>*p_s = son_node;
		RB_Node<T>*p_sl = son_node->left;
		*p_f_from_f = p_s;       //Grand的孩子指针指过来
		p_s->parent = p_f->parent;
		

		p_f->color = rb_red;
		p_s->color = rb_black;


		p_f->right = p_sl;
		if (p_sl)p_sl->parent = p_f;

		p_s->left = p_f;
		p_f->parent = p_s;
		

		}
	else

	{
		//cout << "R型单旋转" << endl;
		RB_Node<T>*p_f = father_node;  //add_from_son
		RB_Node<T>**p_f_from_f = _get_add_from_father(father_node);
		RB_Node<T>*p_s = son_node;
		RB_Node<T>*p_sl = son_node->right;
		*p_f_from_f = p_s;   //修改父节点对应指针
		p_s->parent = p_f->parent;

		p_f->color = rb_red;
		p_s->color = rb_black;

		p_f->left = p_sl;
		if (p_sl) { p_sl->parent = p_f; }

		p_s->right = p_f;
		p_f->parent = p_s;//这个会修改_double_rotate father_node的值
	
		
	}
}

template<typename T>
inline  RB_Node<T>** RB_Tree<T>::  _get_add_from_father(RB_Node<T>*_node)
{
	return _node->parent ? (_node->parent->left == _node? &(_node->parent->left) : &(_node->parent->right)) : &root; 
}


template<typename T>
void RB_Tree<T>:: _double_rotate(RB_Node<T>**father_node, RB_Node<T>*son_node, DEEP_DIRECTION _first_dir)
{
	if (_first_dir == R)  //先右旋 再左旋转   对应RL型
	{
		RB_Node<T>*inital_f = *father_node;
		_single_rotate(son_node,son_node->left, R);
		_single_rotate(inital_f, inital_f->right, L);
	}
	else  //LR
	{
		RB_Node<T>*inital_f = *father_node;
		
		_single_rotate(son_node, son_node->right, L);
		_single_rotate(inital_f, inital_f->left, R);
	}
}