#include "Kuznechik.hpp"



static const uint8_t key[KEY_SIZE] = {
                        0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01,
                        0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
                        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
                        0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88
                        };

int main(int argc, char **argv)
{
    uint8_t encrypt_test_string[BLOCK_SIZE];
    uint8_t decrypt_test_string[BLOCK_SIZE];

    char string[256];

    printf("Please enter your message: ");
    scanf("%s", string);

    if(strlen(string) % BLOCK_SIZE != 0)
    {
        strncat(string, "aaaaaaaaaaaaaaaaa", 16 - strlen(string) % BLOCK_SIZE);
    }

    std::printf("Current string is: %s\n", string);

    for(int i = 0; i < strlen(string) / 16; ++i)
    {
        uint8_t message[BLOCK_SIZE];
        memcpy(message, string + i * 16, 16);

        ExpandKey(key);
        Encrypt(message, encrypt_test_string);
        Decrypt(encrypt_test_string, decrypt_test_string);
    }
    return 0;
}
