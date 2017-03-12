#include "crypto.h"

// Tell CATCH to define its main function here
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define BUFFER_SIZE 512

bool file_exists(const char *fileName) {
  std::ifstream file(fileName);
  return file.is_open();
}

bool isFilesEqual(const char *lFilePath, const char *rFilePath) {
  std::ifstream lFile(lFilePath, std::ifstream::in | std::ifstream::binary);
  std::ifstream rFile(rFilePath, std::ifstream::in | std::ifstream::binary);

  if(!lFile.is_open() || !rFile.is_open()) {
    return false;
  }

  char *lBuffer = new char[BUFFER_SIZE]();
  char *rBuffer = new char[BUFFER_SIZE]();

  do {
    lFile.read(lBuffer, BUFFER_SIZE);
    rFile.read(rBuffer, BUFFER_SIZE);

    if (std::memcmp(lBuffer, rBuffer, BUFFER_SIZE) != 0) {
      delete[] lBuffer;
      delete[] rBuffer;
      return false;
    }
  } while (lFile.good() || rFile.good());

  delete[] lBuffer;
  delete[] rBuffer;
  return true;
}

const unsigned char key[16] = { 'h', 'e', 's', 'l', 'o' };
const unsigned char badKey[16] = { 'h', 'e', 's', 'l',};
unsigned char iv[16] = { 14, 31, 6, 126, 18, 12, 36, 70, 100, 9, 42, 51, 111, 84, 3, 25 };
unsigned char iv2[16] = { 14, 31, 6, 126, 18, 12, 36, 70, 100, 9, 42, 51, 111, 84, 3, 25 };
unsigned char iv3[16] = { 14, 31, 6, 126, 18, 12, 36, 70, 100, 9, 42, 51, 111, 84, 3, 25 };

TEST_CASE("Crypt testing") {
  CHECK(encrypt("Test/noexists", "Test/enc", key, iv) == FILE_NOT_EXIST);
  CHECK(encrypt("Test/plain", "Test/enc", key, iv) == 0);
  CHECK(file_exists("Test/enc") == true);

  CHECK(decrypt("Test/noexists", "Test/enc", key, iv) == FILE_NOT_EXIST);
  CHECK(decrypt("Test/enc", "Test/dec", key, iv2) == 0);
  CHECK(isFilesEqual("Test/plain", "Test/dec") == true);

  CHECK(decrypt("Test/enc", "Test/dec", key, iv) == 0);
  CHECK(isFilesEqual("Test/plain", "Test/dec") == false);

  CHECK(decrypt("Test/enc", "Test/dec", badKey, iv3) == 0);
  CHECK(isFilesEqual("Test/plain", "Test/dec") == false);
}

TEST_CASE("Hash testing") {
  CHECK(hash512("Test/noexists", "Test/hash") == FILE_NOT_EXIST);
  CHECK(hash512("Test/plain", "Test/hash") == 0);
  CHECK(file_exists("Test/hash") == true);
  CHECK(isFilesEqual("Test/hashTest", "Test/hash") == true);

  CHECK(verifyHash512("Test/noexists", "Test/hash") == FILE_NOT_EXIST);
  CHECK(verifyHash512("Test/plain", "Test/noexists") == HASH_FILE_NOT_EXIST);
  CHECK(verifyHash512("Test/plain", "Test/hashTest") == 0);
}
