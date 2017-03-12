#include <stdio.h>
#include "crypto.h"

int main(int argc, char const *argv[]) {

  const unsigned char key[16] = { 'h', 'e', 's', 'l', 'o' };
  unsigned char iv[16] = { 14, 31, 6, 126, 18, 12, 36, 70, 100, 9, 42, 51, 111, 84, 3, 25 };
  unsigned char iv2[16] = { 14, 31, 6, 126, 18, 12, 36, 70, 100, 9, 42, 51, 111, 84, 3, 25 };

//  encrypt("Test/plain", "Test/enc", key, iv);
//  decrypt("Test/enc", "Test/dec", key, iv2);

  hash512("Test/plain", "Test/hash");
  hash512("Test/plain", "Test/hash");
  printf("%d\n", verifyHash512("Test/plain", "Test/hash"));


  return 0;
}
