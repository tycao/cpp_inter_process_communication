#include <iostream>
#include <memory>
using namespace std;

#include <boost/date_time.hpp>
#include <boost/thread.hpp>
using namespace boost;


class MyCls
{
public:
    void operator()()
    {
        for (char c = 'a'; c <= 'z'; ++c)
            cout << c;
    }
};

void F1(void){
    MyCls obj;
    thread thrd4(obj);
    for (int i = 0; i < 10; ++i)
    {
        this_thread::sleep(posix_time::milliseconds(500));
        cout << i;
    }
    cout << "\n" << endl;
    thrd4.join();
}

void F2(void){
    for (char c = 'a'; c <= 'z'; ++c)
    {
        this_thread::sleep(posix_time::milliseconds(500));
        cout << c;
    }
    cout << "\n";
}
thread_local char g_i = 0;
void F5(void)
{
    for (g_i = 'a'; g_i < 'z'; ++g_i)
        cout << g_i;
}
void print()
{
    cout << g_i << endl;
}


mutex g_mtx;
timed_mutex g_mtx2;

void F6(void)
{
    for (int i = 0; i < 10; ++i)
    {
        g_mtx.lock();
        g_i = g_i - 1;
        g_mtx.unlock();
        this_thread::sleep(posix_time::milliseconds(20));
    }
    print();
}
void F7(void)
{
    g_mtx.lock();
    g_i = g_i - 1;
    g_mtx.unlock();
    this_thread::sleep(posix_time::milliseconds(20));
}

int main(int argc, char *argv[])
{
/*
    std::function<int()> ftor = []()->int
    {

    };
    thread thrd1(&F1);
    thread thrd2(&F2);

    MyCls obj;
    //thread thrd3(obj);
    thrd1.join();
    if (thrd2.joinable())
        thrd2.timed_join(posix_time::milliseconds(200));
    thrd2.join();
    //thrd3.join();
*/
    thread thrd1(F5);
    thread thrd2(F5);
    thread thrd3(F5);
    thrd1.join();
    thrd2.join();
    thrd3.join();
    return 0;
}
