#include <iostream>
using namespace std;

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
using namespace boost::interprocess;

int main(int argc, char *argv[])
{
    file_mapping fh("E:/json_tycao.json", read_write);
    mapped_region mp(fh, read_write);
    char* p = (char*)mp.get_address();

    memset(p + 10, 'a', 10);
    cout << (void*)p << " " << p << endl;

    return 0;
}
