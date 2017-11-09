static void MD5_Final(unsigned char digest[16], MD5_CTX *ctx)
{
  win32_crypto_final(ctx, digest, 16);
}