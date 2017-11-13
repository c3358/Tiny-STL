#include<iostream>

using namespace std;
template <class T>
struct MyIter{
    typedef T Iter_type;
    T* ptr;
    MyIter(T* p=0):ptr(p){}
    T& operator*() const{
        return *ptr;
    }
};
template <class T>
struct MyIter<T*>{
    typedef T Iter_type;
    T* ptr;
    MyIter(T* p=0):ptr(p){}
    T& operator*() const{
        return *ptr;
    }
};

template<class T>
struct traits{
    typedef typename T::Iter_type traits_type;
};

template<class T>
struct traits<T*>{
    typedef  T traits_type;
};

//template<class T>
//struct traits<const T*>{
//    typedef T traits_type;
//};

template <class I>
typename traits<I>::traits_type func(I iter){
    return *iter;
}


int main(){
    MyIter<int>iter1(new int(8));
    MyIter<int*>iter2(new int(8));
    cout<<func(iter1)<<endl<<func(iter2);
}
