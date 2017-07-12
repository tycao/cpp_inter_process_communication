#include <iostream>
using namespace std;

#include <boost/thread.hpp>
using namespace boost;

mutex g_mtx;
condition_variable g_builder;
condition_variable g_user;

timed_mutex g_mtxTm;
shared_mutex g_mtxSh;
recursive_mutex g_mtxRe;

int g_i = 0;

void Builder(void)
{
    unique_lock<mutex> lck(g_mtx);
    cout << "Builder1 begin" << endl;
    for (int i = 0; i < 5; ++i)
    {
        ++g_i;
        cout << "Builder1: " << g_i << endl;
        g_user.notify_all();
        g_builder.wait(lck);
    }
    cout << "Builder end" << endl;
    g_user.notify_all();
}

void User1(void)
{

    unique_lock<mutex> lck(g_mtx);
    cout << "User1 begin" << endl;
    for (int i = 0; i < 5; ++i)
    {
        cout << "User1: " << g_i << endl;
        g_builder.notify_one();
        g_user.wait(lck);
    }
    cout << "User1 end" << endl;
    g_builder.notify_all();
}
int main(int argc, char *argv[])
{
    thread thr(Builder);
    thread thr2(User1);
    thr.join();
    thr2.join();
    return 0;
}
