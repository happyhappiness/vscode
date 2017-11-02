static void SHA256_Final(unsigned char digest[32], SHA256_CTX *ctx)
{
  win32_crypto_final(ctx, digest, 32);
}