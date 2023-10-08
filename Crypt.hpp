#ifndef KUZNECHIK
#define KUZNECHIK

#include "Interactive.hpp"

#define BLOCK_SIZE 16
#define KEY_SIZE 32
typedef unsigned char uint8_t;
typedef uint8_t vect[BLOCK_SIZE];

static const uint8_t Pi[256] = {
                                0xFC, 0xEE, 0xDD, 0x11, 0xCF, 0x6E, 0x31, 0x16,
                                0xFB, 0xC4, 0xFA, 0xDA, 0x23, 0xC5, 0x04, 0x4D,
                                0xE9, 0x77, 0xF0, 0xDB, 0x93, 0x2E, 0x99, 0xBA,
                                0x17, 0x36, 0xF1, 0xBB, 0x14, 0xCD, 0x5F, 0xC1,
                                0xF9, 0x18, 0x65, 0x5A, 0xE2, 0x5C, 0xEF, 0x21,
                                0x81, 0x1C, 0x3C, 0x42, 0x8B, 0x01, 0x8E, 0x4F,
                                0x05, 0x84, 0x02, 0xAE, 0xE3, 0x6A, 0x8F, 0xA0,
                                0x06, 0x0B, 0xED, 0x98, 0x7F, 0xD4, 0xD3, 0x1F,
                                0xEB, 0x34, 0x2C, 0x51, 0xEA, 0xC8, 0x48, 0xAB,
                                0xF2, 0x2A, 0x68, 0xA2, 0xFD, 0x3A, 0xCE, 0xCC,
                                0xB5, 0x70, 0x0E, 0x56, 0x08, 0x0C, 0x76, 0x12,
                                0xBF, 0x72, 0x13, 0x47, 0x9C, 0xB7, 0x5D, 0x87,
                                0x15, 0xA1, 0x96, 0x29, 0x10, 0x7B, 0x9A, 0xC7,
                                0xF3, 0x91, 0x78, 0x6F, 0x9D, 0x9E, 0xB2, 0xB1,
                                0x32, 0x75, 0x19, 0x3D, 0xFF, 0x35, 0x8A, 0x7E,
                                0x6D, 0x54, 0xC6, 0x80, 0xC3, 0xBD, 0x0D, 0x57,
                                0xDF, 0xF5, 0x24, 0xA9, 0x3E, 0xA8, 0x43, 0xC9,
                                0xD7, 0x79, 0xD6, 0xF6, 0x7C, 0x22, 0xB9, 0x03,
                                0xE0, 0x0F, 0xEC, 0xDE, 0x7A, 0x94, 0xB0, 0xBC,
                                0xDC, 0xE8, 0x28, 0x50, 0x4E, 0x33, 0x0A, 0x4A,
                                0xA7, 0x97, 0x60, 0x73, 0x1E, 0x00, 0x62, 0x44,
                                0x1A, 0xB8, 0x38, 0x82, 0x64, 0x9F, 0x26, 0x41,
                                0xAD, 0x45, 0x46, 0x92, 0x27, 0x5E, 0x55, 0x2F,
                                0x8C, 0xA3, 0xA5, 0x7D, 0x69, 0xD5, 0x95, 0x3B,
                                0x07, 0x58, 0xB3, 0x40, 0x86, 0xAC, 0x1D, 0xF7,
                                0x30, 0x37, 0x6B, 0xE4, 0x88, 0xD9, 0xE7, 0x89,
                                0xE1, 0x1B, 0x83, 0x49, 0x4C, 0x3F, 0xF8, 0xFE,
                                0x8D, 0x53, 0xAA, 0x90, 0xCA, 0xD8, 0x85, 0x61,
                                0x20, 0x71, 0x67, 0xA4, 0x2D, 0x2B, 0x09, 0x5B,
                                0xCB, 0x9B, 0x25, 0xD0, 0xBE, 0xE5, 0x6C, 0x52,
                                0x59, 0xA6, 0x74, 0xD2, 0xE6, 0xF4, 0xB4, 0xC0,
                                0xD1, 0x66, 0xAF, 0xC2, 0x39, 0x4B, 0x63, 0xB6
                                };

static const uint8_t l_vec[BLOCK_SIZE] = {
                                    1, 148, 32, 133, 16, 194, 192, 1,
                                    251, 1, 192, 194, 16, 133, 32, 148
                                  };
static uint8_t iter_C[32][BLOCK_SIZE];
static uint8_t iter_key[10][BLOCK_SIZE];

//Определение всех функций
static uint8_t multiply(const uint8_t a, const uint8_t b);
static void X(const uint8_t* a, const uint8_t* b, uint8_t *c);
static void R(uint8_t* state);
static void L(const uint8_t *in_data, uint8_t *out_data);
static void GetC();
static void ExpandKey(const uint8_t *key);
static void F(const uint8_t *in_key_1, const uint8_t *in_key_2,
                        uint8_t *out_key_1, uint8_t *out_key_2,
                        uint8_t *iter_const);
static void S(const uint8_t *in_data, uint8_t *out_data);

static void S(const uint8_t *in_data, uint8_t *out_data)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
        out_data[i] = Pi[in_data[i]];
}

static void X(const uint8_t* a, const uint8_t* b, uint8_t *c)
{
    for(int i = 0; i < BLOCK_SIZE; i++)
    {
        c[i] = a[i] ^ b[i];
    }
}

static void R(uint8_t* state)
{
     int i;
    uint8_t a_15 = 0;
    vect internal;
    for (i = 15; i >= 0; i--)
    {
        if (i - 1 >= 0)
            internal[i - 1] = state[i];
        a_15 ^= multiply(state[i], l_vec[i]);
    }
    internal[15] = a_15;
    memcpy(state, internal, BLOCK_SIZE);
}

static uint8_t multiply(uint8_t a, uint8_t b)
{
    uint8_t c = 0;
    uint8_t hi_bit;
    int i;
    for (i = 0; i < 8; i++)
    {
        if (b & 1)
            c ^= a;
        hi_bit = a & 0x80;
        a <<= 1;
        if (hi_bit)
            a ^= 0xc3; //полином x^8+x^7+x^6+x+1
        b >>= 1;
    }
    return c;
}

static void L(const uint8_t *in_data, uint8_t *out_data)
{
    int i;
    vect internal;
    memcpy(internal, in_data, BLOCK_SIZE);
    for (i = 0; i < 16; i++)
        R(internal);
    memcpy(out_data, internal, BLOCK_SIZE);
}

static void GetC()
{
    int i;
    vect iter_num[32];
    for (i = 0; i < 32; i++)
    {
        memset(iter_num[i], 0, BLOCK_SIZE);
        iter_num[i][0] = i+1;
    }
    for (i = 0; i < 32; i++)
         L(iter_num[i], iter_C[i]);
}

static void F(const uint8_t *in_key_1, const uint8_t *in_key_2,
                        uint8_t *out_key_1, uint8_t *out_key_2,
                        uint8_t *iter_const)
{
    vect internal;
    memcpy(out_key_2, in_key_1, BLOCK_SIZE * sizeof(uint8_t));
    X(in_key_1, iter_const, internal);
    L(internal, internal);
    S(internal, internal);
    X(internal, in_key_2, out_key_1);
}

static void ExpandKey(const uint8_t *key)
{
    int i;
    uint8_t key_1[KEY_SIZE/2];
    uint8_t key_2[KEY_SIZE/2];
    uint8_t iter_1[KEY_SIZE/2];
    uint8_t iter_2[KEY_SIZE/2];
    uint8_t iter_3[KEY_SIZE/2];
    uint8_t iter_4[KEY_SIZE/2];
    memcpy(key_1, key + KEY_SIZE/2, KEY_SIZE/2);
    memcpy(key_2, key, KEY_SIZE/2);
    GetC();
    memcpy(iter_key[0], key_1, KEY_SIZE/2);
    memcpy(iter_key[1], key_2, KEY_SIZE/2);
    memcpy(iter_1, key_1, KEY_SIZE/2);
    memcpy(iter_2, key_2, KEY_SIZE/2);
    for (i = 0; i < 4; i++)
    {
        F(iter_1, iter_2, iter_3, iter_4, iter_C[0 + 8 * i]);
        F(iter_3, iter_4, iter_1, iter_2, iter_C[1 + 8 * i]);
        F(iter_1, iter_2, iter_3, iter_4, iter_C[2 + 8 * i]);
        F(iter_3, iter_4, iter_1, iter_2, iter_C[3 + 8 * i]);
        F(iter_1, iter_2, iter_3, iter_4, iter_C[4 + 8 * i]);
        F(iter_3, iter_4, iter_1, iter_2, iter_C[5 + 8 * i]);
        F(iter_1, iter_2, iter_3, iter_4, iter_C[6 + 8 * i]);
        F(iter_3, iter_4, iter_1, iter_2, iter_C[7 + 8 * i]);
        memcpy(iter_key[2 * i + 2], iter_1, KEY_SIZE/2);
        memcpy(iter_key[2 * i + 3], iter_2, KEY_SIZE/2);
    }
for(int i = 0; i < 10; i++)
    Print(iter_key[i]);
}
#endif //KUZNECHIK