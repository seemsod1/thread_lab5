#include <iostream>
#include <string>
#include <thread>
#include <syncstream>
#include <future>
#include <vector>


using namespace std;




void process(const string& name, int time) {
    std::this_thread::sleep_for(std::chrono::seconds(time));
    std::thread::id this_id = std::this_thread::get_id();
    std::osyncstream(std::cout) << "[" << this_id << "] "+ name +" is called\n";
}

void work() {
    auto start = std::chrono::high_resolution_clock::now();



    std::future<void> th1 = std::async(std::launch::deferred, process,"D2", 1);
    std::future<void> th2 = std::async(std::launch::async, process, "B", 1);
    std::future<void> th3 = std::async(std::launch::async, process, "A1", 7);
    std::future<void> th4 = std::async(std::launch::async, process, "C", 7);



    th1.wait();
    th1 = std::async(std::launch::deferred, process,"F2", 1);

th1.wait();
th2.wait();
th3.wait();
th4.wait();

    th1 = std::async(std::launch::deferred, process,"D1", 1);
    th1.wait();
    th1 = std::async(std::launch::deferred, process,"F1", 1);

    th1.wait();


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::osyncstream(std::cout) << "Work is done\nIt's took " << elapsed.count() << " seconds\n";
}

int main() {
    work();
    return 0;
}
