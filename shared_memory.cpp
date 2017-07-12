#include <iostream>
using namespace std;

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

using namespace boost;
using namespace boost::interprocess;


class MyMtx
{
public:
    interprocess_mutex m_mtx;
};


int main(int argc, char *argv[])
{
    shared_memory_object::remove("MyName");
    managed_shared_memory msm(create_only, "MyName", 1024);
    int* pi = msm.construct<int>("MyInt")(0);
    for (int i = 0; i < 100; ++i, ++(*pi)) ;

    return 0;
}
