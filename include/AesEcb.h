#ifndef AESECB_H
#define AESECB_H

#include <Arduino.h>
#include "mbedtls/aes.h"

class AesEcb
{
  public:
    AesEcb(byte* key, int keyLength);
    ~AesEcb();
    void encrypt(byte* plaintext, byte* ciphertext);
    void decrypt(byte* ciphertext, byte* plaintext);
    void setKey(byte* key, int keyLength);
  
  private:
    byte key[16];
    mbedtls_aes_context aes;
};

#endif // AESECB_H