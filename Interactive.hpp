#ifndef INTERACTIVE
#define INTERACTIVE

#include <iostream>
#include "Math.hpp"

void Print(uint8_t a)
{
    std::cout << Byte(a) << std::endl;
}
void Print(uint8_t* a)
{
    for(int i = 0; i < 16; ++i)
    {    
        printf("%02x", a[i]);
    }
    std::cout << std::endl;
}

#endif //INTERACTIVE