#include "list-iter.h"
#include<iostream>
#include<algorithm>

using namespace std;
int main()
{
 List<int> mylist;
 for(int i=1; i<5; ++i) {

 mylist.insert_front(i);
 mylist.insert_front(i*2);
 }
 mylist.display();

// ListIter<ListItem<int> >begin(mylist.front());
// ListIter<ListItem<int> >end(mylist.end());
// ListIter<ListItem<int> > iter(nullptr);

//iter = find(begin, end, 3);
// if (iter == end)
// cout << "not found" << endl;
// else
// cout << "found. " << iter->value() << endl;
return 0;
}
