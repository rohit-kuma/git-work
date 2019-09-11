Threads and data races
A thread of execution is a flow of control within a program that begins with the invocation of a top-level function by std::thread::thread, std::async, or other means. 
Any thread can potentially access any object in the program (objects with automatic and thread-local storage duration may still be accessed by another thread through a pointer or by reference). 
Different threads of execution are always allowed to access (read and modify) different memory locations concurrently, with no interference and no synchronization requirements. 
When an evaluation of an expression writes to a memory location and another evaluation reads or modifies the same memory location, the expressions are said to conflict. A program that has two conflicting evaluations has a data race unless 
both evaluations execute on the same thread or in the same signal handler, or 
both conflicting evaluations are atomic operations (see std::atomic), or 
one of the conflicting evaluations happens-before another (see std::memory_order) 
If a data race occurs, the behavior of the program is undefined. 
(in particular, release of a std::mutex is synchronized-with, and therefore, happens-before acquisition of the same mutex by another thread, which makes it possible to use mutex locks to guard against data races) 
int cnt = 0;
auto f = [&]{cnt++;};
std::thread t1{f}, t2{f}, t3{f}; // undefined behavior
std::atomic<int> cnt{0};
auto f = [&]{cnt++;};
std::thread t1{f}, t2{f}, t3{f}; // OK
