
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
	stack<pair<AVL_Node<T>**,DEEP_DIRECTION>> src;   //��¼������·�������ڸ߶�����,���Ч�ʵ����ӿռ俪����
	AVL_Node<T> **cur_node = &root;
	while (true)
	{
		if (value > (*cur_node)->data) {				//>
			pair<AVL_Node<T>**, DEEP_DIRECTION> mem_for_src = make_pair(cur_node,R);
			src.push(mem_for_src);//·����ջ
			if ((*cur_node)->right) {
				cur_node = &((*cur_node)->right);
			}
			else {															//insert �Ҳ�
				AVL_Node<T>* new_node = new AVL_Node<T>(value, nullptr, nullptr,1);
				(*cur_node)->right = new_node;
				if ((*cur_node)->left == nullptr)//�ýڵ�Ҳ��������ڵ� ����ô���߶�Ҫ�任
						_is_balance(src);       //���ݼ�鲢�������
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
	if (src.size() == 1)  //��ֻ��1���ڵ��·�� ��һ��ƽ��� ���ڵ�Ĳ��벻�ᴥ���ú��� ���Բ���Ϊ0
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
	{  //��ǰѭ����father�ڵ㱾��߶�û�иı�
		if (father_node.second == L)
		{
		if (  tree_height((*(father_node.first))->left)+1<= tree_height((*(father_node.first))->right)  )//�����ǰ�ڵ���Ӧ������߸߶�û�����壬Ҳ��������
		return;
		else (*(father_node.first))->left->height++;
		}

		else {
			if (tree_height((*(father_node.first))->right) + 1 <= tree_height((*(father_node.first))->left))//�����ǰ�ڵ���Ӧ������߸߶�û�����壬Ҳ��������
				return;
			else (*(father_node.first))->right->height++;
		}
		
		if (abs(tree_height((*(father_node.first))->left) - tree_height((*(father_node.first))->right)) == 2)//
		{
			int high_direction = father_node.second;
			int deep_direction = son_node.second;
			ROTATE_DIRECTION rotate_dir_=(ROTATE_DIRECTION)(2*high_direction + deep_direction);
			//Ҫ������ת
			(*(father_node.first))->height++;
			int hf = (*(father_node.first))->height;
			int hs = (*(son_node.first))->height;
			
			_fix(father_node.first, son_node.first, rotate_dir_);   //_fix���ܵ��Ƕ���ָ�룬��rotate�������ԭ������
			return;
				
		}
		    if (src.empty())break;
			son_node = father_node;
			father_node = src.top();
			src.pop();
	} 


	/*((*(father_node.first))->height)++;*/
	//�ܵ�����һ����ֻʣ�¸��ڵ� ��*father_node ����root
	root->height = max(root->left->height, root->right->height) + 1;
}

template<typename T>
void AVL_Tree<T>::_fix(AVL_Node<T>**father_node, AVL_Node<T>**son_node, ROTATE_DIRECTION _dir)
{
	switch (_dir)
	{
	case LL:
		cout << "LL" <<" ";
		_single_rotate(*father_node, *son_node, R); //�ҵ���ת
		break;
	case LR:
		cout << "LR" << " ";
		_double_rotate(father_node, son_node, L);   //˫��ת�����Һ���
		break;
	case RL:
		cout << "RL" << " ";
		_double_rotate(father_node, son_node, R);//˫ѡת ������ұ�
		break;
	case RR:
		cout << "RR" << " ";
		_single_rotate(*father_node, *son_node, L);//����ת
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
		//int width =100;       //ģ��ģ��λ��(d

		int count_of_cur_nodes = 1;
		int count_of_next_nodes = 0;

		queue<AVL_Node<T>*>que_tree;
		que_tree.push(root);

		AVL_Node<T>*cur_node;
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
	if (_dir == L) //����   //��Ӧ����תRR��̬ RR����ת���ڵ㰴-2����
	{
		AVL_Node<T>*p_f=father_node;
		AVL_Node<T>*p_s = son_node;
		AVL_Node<T>*p_sl = son_node->left;

		p_f->right = p_sl;
		p_s->left = p_f;
		p_f->height=max(tree_height(p_f->left),tree_height(p_f->right))+1;//�����߶�
		p_s->height= max(tree_height(p_s->left), tree_height(p_s->right)) + 1;
		father_node = p_s;
	}
	else               //���� //��Ӧ����תLL��̬
	{
		AVL_Node<T>*p_f = father_node;
		AVL_Node<T>*p_s = son_node;
		AVL_Node<T>*p_sl = son_node->right;

		p_f->left = p_sl;
		p_s->right = p_f;
		p_f->height = max(tree_height(p_f->left), tree_height(p_f->right)) + 1;//�����߶�
		p_s->height = max(tree_height(p_s->left), tree_height(p_s->right)) + 1;
		father_node = p_s;
	}

}

template<typename T>
void AVL_Tree<T>::_double_rotate(AVL_Node<T>**father_node, AVL_Node<T>**son_node, DEEP_DIRECTION _first_dir)
{

	if (_first_dir == R)  //������ ������ת   ��ӦRL��
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