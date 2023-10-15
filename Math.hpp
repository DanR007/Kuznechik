#ifndef MATH
#define MATH

#include <stdfix.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include <cmath>

typedef unsigned char uint8_t;

void FromHexToDecArr(const std::string& hex, uint8_t* dec);
uint8_t Byte(const std::string& hex);
void FromDecArrToHex(uint8_t* dec, std::string& hex);
std::string Byte(uint8_t dec);

uint8_t Byte(const std::string& hex)
{
    std::string h = "0123456789abcdef";

    uint8_t byte = 0;
    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 16; ++j)
        {
            if(h[j] == hex[i])
            {
                byte += j * std::pow(16, i);
            }
        }
    }

    return byte;
}

std::string Byte(uint8_t dec)
{
    const std::string h = "0123456789abcdef";
    std::string hex = "";

    hex += h[dec / 16];
    hex += h[dec % 16];

    return hex;
}

void FromHexToDecArr(const std::string& hex, uint8_t* dec)
{
    for(int i = 0; i < hex.size(); ++i)
    {
        dec[i] = Byte(hex.substr(i * 2, 2));
    }
}

void FromDecArrToHex(uint8_t* dec, std::string& hex)
{
    for(int i = 0; i < 16; ++i)
    {
        hex += Byte(dec[i]);
    }
}
#endif//MATH