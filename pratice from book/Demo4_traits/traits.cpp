#include<iostream>  
using namespace std;  
template <class T>  
struct MyIter{  
    typedef T value_type;  
    T* ptr;  
    MyIter(T* p=0):ptr(p){}  
    T& operator*() const{  
        return *ptr;  
    }  
};  
//偏特化  
template <class T>  
struct MyIter<T*>{  
    typedef T value_type;  
    T* ptr;  
    MyIter(T* p=0):ptr(p){}  
    T& operator*() const{  
        return *ptr;  
    }  
};  
  
template<class T>  
struct my_iterator_traits{  
    typedef typename T::value_type value_type;//注意必须有typename  
};  
  
//对原生指针T偏特化  
template<class T>  
struct my_iterator_traits<T*>{  
    typedef  T value_type;  
};  
//对指向常对象的原生指针偏特化  
template<class T>  
struct my_iterator_traits<const T*>{  
    typedef T value_type;  
};  
  
template <class I>  
typename my_iterator_traits<I>::value_type func(I iter){  
    return *iter;  
}  
  
  
  
int main(){  
  
    MyIter<int>iter1(new int(8));  
    MyIter<int*>iter2(new int(8));  
    cout<<func(iter1)<<endl<<func(iter2);  
} 