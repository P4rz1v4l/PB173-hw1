#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdio.h>
#include <fstream>
#include <cstring>
#include "mbedtls/aes.h"
#include "mbedtls/sha512.h"

#define FILE_NOT_EXIST 1
#define KEY_SET_FAIL 2
#define ENCRYPT_FAIL 3

#define SHA512 0
#define HASH_FILE_NOT_EXIST 2
#define HASH_OK 3
#define HASH_BAD 4


unsigned int encrypt(const char *input, const char *output, const unsigned char key[32], unsigned char iv[16]);

unsigned int decrypt(const char *input, const char *output, const unsigned char key[32], unsigned char iv[16]);

unsigned int hash512(const char *input, const char *hashFile);

int verifyHash512(const char *input, const char *hashFile);


#endif
