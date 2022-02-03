#include "reception.hpp"
#include <iostream>

int main(int argc,char* argv[])
{
    Reception reception(argv[FIRST], argv[SECOND]);
    reception.enter_order();
    return 0;
}