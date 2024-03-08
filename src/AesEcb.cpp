#include "AesEcb.h"


AesEcb::AesEcb(byte* key, int keyLength)
{
  mbedtls_aes_init(&aes);
  setKey(key, keyLength);
}

AesEcb::~AesEcb()
{
  mbedtls_aes_free(&aes);
}

void AesEcb::setKey(byte* key, int keyLength)
{
  if(keyLength != 16)
    throw "Invalid key length";

  mbedtls_aes_setkey_enc(&aes, key, 128);
  mbedtls_aes_setkey_dec(&aes, key, 128); 
}

void AesEcb::encrypt(byte* plaintext, byte* ciphertext)
{
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, plaintext, ciphertext);
}

void AesEcb::decrypt(byte* ciphertext, byte* plaintext)
{
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, ciphertext, plaintext); 
}