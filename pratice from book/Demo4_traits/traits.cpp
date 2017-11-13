#include<iostream>
template <typename T>
struct  Traits{
    typedef T _type;

};
template<>
struct  Traits<float>{
    typedef int _type;
};

template <typename T>
class A
{
public:
  A(T a,T b):data_a(a),data_b(b){};
  typename Traits<T>::_type sum(){return data_a+data_b;}

private:
  T data_a,data_b;
};



int main()
{
    A<double>Obj_d(1.3,1.5);
    A<float>Obj_f(1.3,1.5);
    std::cout<<Obj_d.sum()<<" "<<Obj_f.sum();
    return 0;
}
