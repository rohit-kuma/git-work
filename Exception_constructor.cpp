How to Handle exception at C++ constructor using Boost's Shared Ptr
Score: 3.2/5 (137 votes)

Its a very common problem in C++ that if a class's constructor throws an exception (say memory allocation exception) how we should handle it. Think about the following piece of code. Here class A's constructor has thrown an exception.. so the best way to handle such situation is to instantiate A inside a try block...if exception is thrown in the constructor of A, i will be destroyed by stack unwinding and the thrown exception will be caught...

class MyException(string str){
private: 
string  msg;
public:
MyException(string str){
msg = str;
}
void printerrmsg(){
cout<<msg.c_str()<<endl;
}
}

class A{
private: int i;

//if exception is thrown in the constructor of A, i will de destroyed by stack unwinding
//and the thrown exception will be caught
A()
{
i = 10;
throw MyException(“Exception thrown in constructor of A()”);
}
};
void main(){
try{
A();
}
catch(MyException& e){
e.printerrmsg();
}
}
Edit & Run

now there is another point... suppose we need to allocate some dynamic memory in the constructor... and while doing that the constructor throws a memory exception... so the stack based pointer which was referencing the heap based memory will be destroyed because of the stack unwinding... so we will have some memory which is referenced by no pointer and hence we cannot access that... so obviously its a memory leak... so, how can we handle that...

the best way to handle this kind of situation in modern C++ is to use auto_ptr/shared_ptr... so the solution will look something as the following:


#include <iostream>
#include <string>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

using namespace std;

class SomeClass{
public:
 SomeClass(){}
 ~SomeClass(){};
};

typedef boost::shared_ptr<SomeClass> pSomeClass;
typedef boost::shared_ptr<char> pChar;
typedef boost::shard_array<char> charBuff;

class MyException{
public:
 MyException(string str){
 msg = str;
 }
 void printerrmsg(){
  cout<<msg.c_str()<<endl;
 }
private:
 string msg;
};
class A{
private:
 int i;
 pChar m_ptrChar;
 pSomeClass m_ptrSomeClass;
 charBuff m_pcharBuff;

 //if exception is thrown in the constructor of A, i will be destroyed by stack unwinding
 //and the thrown exception will be caught
public:
 A():m_ptrChar(new char),m_ptrSomeClass(new SomeClass),m_pcharBuff(new char[100])
 {
 i = 10;
 throw MyException("Exception at A's constructor");
 }
};

int main(){
 try{
 A objA;
 }
 catch(MyException& e){
  e.printerrmsg();
 }
 return 1;
 }
Edit & Run
