#include <iostream>     
using namespace std;
class Derived;
class Base
{
	public:
	Base(){cout<<"Base Constructor"<<endl;}
	Base(int a){cout<<"Base Constructor 1 arg"<<endl;}
	void fun(){cout<<"BFun"<<endl;}
	Derived* clone();
	Derived* operator()();
};
class Derived: public Base
{
	public:
	Derived(){cout<<"Derived Constructor"<<endl;}
	Derived(int a){cout<<"Derived Constructor 1 arg"<<endl;}
	void fun(){cout<<"DFun"<<endl;}
};
Derived* Base::clone(){Derived* obj = new Derived(); return obj;}
Derived* Base::operator()(){Derived* obj = new Derived(); return obj;}
int main()
{
	Derived d,*ptr;
	Base* b = new Derived;
	b->fun();//Derived fun overrides base
	ptr = static_cast<Derived*>(b);
	ptr->fun();//Polymorphism achived using static cast
	b->clone()->fun();//Polymorphism achived using clone function
	(*b)()->fun();//polymorphism achived by functor
	return 0;
}
