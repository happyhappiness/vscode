static bool encrypt_des(const unsigned char *in, unsigned char *out,
                        const unsigned char *key_56)
{
  char key[8];
  size_t out_len;
  CCCryptorStatus err;

  extend_key_56_to_64(key_56, key);
  err = CCCrypt(kCCEncrypt, kCCAlgorithmDES, kCCOptionECBMode, key,
                kCCKeySizeDES, NULL, in, 8 /* inbuflen */, out,
                8 /* outbuflen */, &out_len);
  return err == kCCSuccess;
}