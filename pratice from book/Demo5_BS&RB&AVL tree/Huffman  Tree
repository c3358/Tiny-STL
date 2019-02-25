#include "pch.h"
#include<iostream>
#include<algorithm>
#include<fstream>
#include<math.h>
#include <string>
#include<vector>
#include <stack>
#include<list>
const int ma = 99999999;
using namespace std;
struct node;
struct node 
{
	node(node *lc, node *rc,node*father, double data) {
		this->lc = lc;
		this->rc = rc;
		this->father = father;
		this->data = data;
		
	}
	node *lc;
	node *rc;
	node *father;
	double data;
};
bool is_leaf(node* T)
{
	if (T->lc == nullptr&&T->rc == nullptr)
		return true;
}
int main()
{

	
	//Sample input : 0.1 0.15 0.2 0	.25 0.3
	ifstream  infile("C:\\Users\\inkcherry\\Desktop\\inkc机试练习手册\\testfile\\201307.txt");
	int n = 0;
	double cur;
	list<node*>m;
	vector<node*>st;
	while (!infile.eof())
	{
		infile >> cur;
		node *eee = new node(nullptr, nullptr,nullptr, cur);
		m.push_back(eee);
		st.push_back(eee);
	}

	
	
	node *root=nullptr;
	while (m.size()>1)
	{
		int mi1 = 99, mi2 = 99;
		auto index1 = m.begin();
		auto index2 = m.begin();
		for (auto iter = m.begin(); iter != m.end(); iter++)
		{

			if (mi2 > (*iter)->data)
			{
				mi2 = (*iter)->data;
				index2 = iter;
			}
			if (mi1 > mi2)
			{
				swap(index1, index2);
				swap(mi1, mi2);
			}
		}
		int temp = mi1+mi2;
		node *root = new node(*index1, *index2,nullptr, temp);
		(*index1)->father = root;
		(*index2)->father = root;
		m.erase(index1);
		m.erase(index2);
		m.push_back(root);
	}
	root = *m.begin();
	stack<int>q;
	for (auto iter = st.begin();iter != st.end(); iter++)
	{
		auto temp = *iter;
		auto temp2 = (*iter)->father;
		while ((temp2) != nullptr)
		{
			if (temp2->lc == temp)
				q.push(0);
			else q.push(1);
			temp = temp2;
			temp2 = temp2->father;
		}
		while (!q.empty())
		{
			cout << q.top();
			q.pop();
		}
		cout << endl;

	}
	
	return 0;
}
