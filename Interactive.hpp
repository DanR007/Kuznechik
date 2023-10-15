#ifndef INTERACTIVE
#define INTERACTIVE

#include <iostream>
#include "Math.hpp"

void Print(uint8_t a)
{
    printf("%02x", a);
}
void Print(uint8_t* a)
{
    for(int i = 0; i < 16; ++i)
    {    
        printf("%02x", a[i]);
    }
    printf("\n");
}

#endif //INTERACTIVE