#include "reception.hpp"
#include <iostream>

int main(int argc,char* argv[])
{
    Reception reception(argv[1]);
    reception.enter_order();
    return 0;
}