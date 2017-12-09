#include<iostream>
template <typename T>
class ListItem;

template <typename T>
bool operator!=(const ListItem<T>& item, T n)
{ return item.value() != n; }


template <typename T>
class ListItem
{
public:
  explicit ListItem(T &value)_value:(value){}
  explicit ListItem(T &&value)_value:std::move(value){}

  T value() const { return _value; }
  ListItem* next()  { return _next; }

 T _value;
 ListItem* _next;
};



template <typename T>
class List
{
    public:
     int flag=0;
     List(){_front=_end=nullptr;}
     void insert_end(T &&value);
     void display(std::ostream &os = std::cout) {
     	for (ListItem<T>* p = front(); p != end(); p = p->next())
		os << p->value() << " ";
		os << std::endl;
     }
     ListItem <T>* front(){return _front;}
     ListItem <T>* end() {return _end;}

    template <typename U>
    void insert_front(U &&value){
        //    T m=value;
        ListItem <T>*temp = new ListItem<T>(std::forward<U>(value));

     if(_front!=nullptr){

        temp->_next=_front;
        _front=temp;
        }

     else{

        temp->_next=_end;
        _front=temp;

        }
    }

     ListItem <T>*  _end;
     ListItem <T>*  _front;
     long _size;
};

//template <typename T>
//void List<T>::insert_front(T &value){
//    ListItem <T>*temp = new ListItem<T>(value);
//}
//template <typename T,typename U>
//void List<T>::insert_front(U &&value,T a){  //由于模板类关系 ，参数value并不会起到类型检测，因此这只是一个右值参数。
//    ListItem <T>*temp = new ListItem<T>(std::forward<U>(value));
//}





