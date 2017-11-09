static void SHA1_Final(unsigned char digest[20], SHA_CTX *ctx)
{
  win32_crypto_final(ctx, digest, 20);
}