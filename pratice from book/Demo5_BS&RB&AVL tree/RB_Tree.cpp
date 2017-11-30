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
		root = new RB_Node<T>(value,nullptr, nullptr, nullptr,rb_black);  //���ڵ�Ϊ��ɫ
		return;
	}
	RB_Node<T> *cur_node = root;
	while (true)
	{
		if (value>cur_node->data) {				//>
			if (cur_node->right) {
				cur_node = cur_node->right;
			}
			else {															//insert �Ҳ�
				RB_Node<T>* new_node = new RB_Node<T>(value, cur_node,nullptr, nullptr,rb_red); //Ϊ��ɫ
				cur_node->right = new_node;
				_is_balance(new_node, cur_node, R);  
				return;
			}
		}
		else {										//insert ���
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
	if (tree_color(father_node) == rb_black)  //���׺�ɫ�����޸�
	{
		//cout << "���ڣ�����" << endl;
		return;
	}
	else
	{
		if (father_node->parent)  //ʵ�����ݽṹ�� 
		{
			 RB_Node<T>*uncle_node=nullptr;
			
			
			 DEEP_DIRECTION high_dir;
			//ȷ��������Լ� ��ڵ����ɫ
			 if ((father_node->parent->left) == (father_node))     //����Ϊ����
			 {
				high_dir = L;										
				uncle_node = father_node->parent->right;
				 
			 }
			else if ((father_node->parent->right) == (father_node))   //����Ϊ����
			{	
				high_dir = R;
				uncle_node = father_node->parent->left;
			}
			//
			 
			 if (tree_color(uncle_node) == rb_black) //������ڵĴ��� ��ת����
			 {            
			
				 RB_Node<T>**p_grand_node_from_son = &(father_node->parent);
				 //cout <<"��ڸ���";
				 ROTATE_DIRECTION rotate_dir_ = (ROTATE_DIRECTION)(2 * high_dir + deep_dir);
				 _fix(p_grand_node_from_son, father_node, rotate_dir_);
			 }

			 else                                 //�������Ĵ��� ��������
			 {
				/* cout << "��츸��";*/
				 father_node->color = rb_black;
				 uncle_node->color = rb_black;//Ⱦ��

				 if (father_node->parent->parent == nullptr)  //���Grand�Ǹ��ڵ�
				 {  //ֻȾ�常�ڣ���Ⱦ��Grand
					 return;
				 }
				 else {  
					 //cout << "����һ��" << endl;
					 father_node->parent->color = rb_red;
					 DEEP_DIRECTION grand_dir = father_node->parent->parent->left == father_node->parent ? L : R;
					 _is_balance(father_node->parent, father_node->parent->parent, grand_dir); //�游��Ϊ��ڵ��������
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
	//int width =100;       //ģ��ģ��λ��(d

	int count_of_cur_nodes = 1;
	int count_of_next_nodes = 0;

	queue<RB_Node<T>*>que_tree;
	que_tree.push(root);

	RB_Node<T>*cur_node;
	while (!que_tree.empty())
	{
		cur_node = que_tree.front();
		que_tree.pop();

		if (cur_node->left) {    //�²��һ���ڵ�
			count_of_next_nodes++;
			que_tree.push(cur_node->left);
		}
		if (cur_node->right) {  //�²��һ���ڵ�
			count_of_next_nodes++;
			que_tree.push(cur_node->right);
		}
		std::cout << cur_node->data << "(" << ((cur_node->color)?"��":"��")  ;
		if (cur_node->parent)
			cout << "��" << cur_node->parent->data << ")" << " ";
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
void RB_Tree<T>::_single_rotate(RB_Node<T>*father_node, RB_Node<T>*son_node, DEEP_DIRECTION _dir)  //����ܵĵ�һ������Ϊ�ӽڵ��parentָ��&�����ڵ��Ӧָ���ں����ڼ���
{
	if (_dir == L)  //RR
	{
		RB_Node<T>*p_f = father_node;
		RB_Node<T>**p_f_from_f = _get_add_from_father(father_node);
		RB_Node<T>*p_s = son_node;
		RB_Node<T>*p_sl = son_node->left;
		*p_f_from_f = p_s;       //Grand�ĺ���ָ��ָ����
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
		//cout << "R�͵���ת" << endl;
		RB_Node<T>*p_f = father_node;  //add_from_son
		RB_Node<T>**p_f_from_f = _get_add_from_father(father_node);
		RB_Node<T>*p_s = son_node;
		RB_Node<T>*p_sl = son_node->right;
		*p_f_from_f = p_s;   //�޸ĸ��ڵ��Ӧָ��
		p_s->parent = p_f->parent;

		p_f->color = rb_red;
		p_s->color = rb_black;

		p_f->left = p_sl;
		if (p_sl) { p_sl->parent = p_f; }

		p_s->right = p_f;
		p_f->parent = p_s;//������޸�_double_rotate father_node��ֵ
	
		
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
	if (_first_dir == R)  //������ ������ת   ��ӦRL��
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