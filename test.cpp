#include "forward_list.hpp"

int main() 
{
    my_list::forward_list<int> fw;
    fw.push_front(333);
    fw.push_front(555);
    fw.push_front(666);
    fw.push_front(777);
    fw.print();



    return 0;
}