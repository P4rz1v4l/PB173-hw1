#include "crypto.h"

using namespace std;

bool file_exist(const char *fileName) {
    std::ifstream file(fileName);
    return file.is_open();
}


unsigned int encrypt(const char *input, const char *output, const unsigned char key[32], unsigned char iv[16]) {
  if (!file_exist(input)) {
    return FILE_NOT_EXIST;
  }

  //READ
  ifstream fileIn(input);
  string str((istreambuf_iterator<char>(fileIn)), istreambuf_iterator<char>());

  size_t size = (((str.length() - 1) / 16) + 1) * 16;

  unsigned char *plainText = new unsigned char[size]();
  memcpy(plainText, str.c_str(), str.length());

  //ENCRYPT
  mbedtls_aes_context aes;
  unsigned char *encryptText = new unsigned char[size];
  if(mbedtls_aes_setkey_enc(&aes, key, 128)) {
    return KEY_SET_FAIL;
  }

  mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, size, iv, plainText, encryptText);

  //WRITE
  ofstream fileOut;
  fileOut.open(output);
  copy(encryptText, encryptText + size, ostreambuf_iterator<char>(fileOut));

  delete[] plainText;
  delete[] encryptText;

  return 0;
}



unsigned int decrypt(const char *input, const char *output, const unsigned char key[32], unsigned char iv[16]) {
  if (!file_exist(input)) {
    return FILE_NOT_EXIST;
  }

  //READ
  ifstream fileIn(input);
  string str((istreambuf_iterator<char>(fileIn)), istreambuf_iterator<char>());

  size_t size = (((str.length() - 1) / 16) + 1) * 16;

  unsigned char *encryptText = new unsigned char[size]();
  memcpy(encryptText, str.c_str(), str.length());

  //DECRYPT
  mbedtls_aes_context aes;
  unsigned char *decryptText = new unsigned char[size];
  if(mbedtls_aes_setkey_dec(&aes, key, 128)) {
    return KEY_SET_FAIL;
  }

  mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, size, iv, encryptText, decryptText);

  //WRITE
  ofstream fileOut;
  fileOut.open(output);
  copy(decryptText, decryptText + size, ostreambuf_iterator<char>(fileOut));

  delete[] decryptText;
  delete[] encryptText;

  return 0;
}


unsigned int hash512(const char *input, const char *hashFile) {
  if (!file_exist(input)) {
    return FILE_NOT_EXIST;
  }

  //READ
  ifstream fileIn(input);
  string str((istreambuf_iterator<char>(fileIn)), istreambuf_iterator<char>());

  unsigned char *contetnt = new unsigned char[str.length()]();
  memcpy(contetnt, str.c_str(), str.length());

  //HASH
  unsigned char *hash = new unsigned char[64]();
  mbedtls_sha512(contetnt, str.length(), hash, SHA512);

  //WRITE
  ofstream fileOut;
  fileOut.open(hashFile);
  copy(hash, hash + 64, ostreambuf_iterator<char>(fileOut));

  delete[] contetnt;
  delete[] hash;

  return 0;
}



int verifyHash512(const char *input, const char *hashFile) {
  if (!file_exist(input)) {
    return FILE_NOT_EXIST;
  }

  //READ
  ifstream fileIn(input);
  string str((istreambuf_iterator<char>(fileIn)), istreambuf_iterator<char>());

  unsigned char *contetnt = new unsigned char[str.length()]();
  memcpy(contetnt, str.c_str(), str.length());

  //HASH
  unsigned char *hash = new unsigned char[64]();
  mbedtls_sha512(contetnt, str.length(), hash, SHA512);

  if (!file_exist(hashFile)) {
    return HASH_FILE_NOT_EXIST;
  }
  ifstream fileHash(hashFile);
  string oldHash((istreambuf_iterator<char>(fileHash)), istreambuf_iterator<char>());

  string newHash((char *) hash, 64);

  delete[] contetnt;
  delete[] hash;

  return oldHash.compare(newHash);
}
