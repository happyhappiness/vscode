static void SHA256_Final(unsigned char digest[32], SHA256_CTX *ctx)
{
  memcpy(digest, gcry_md_read(*ctx, 0), 32);
  gcry_md_close(*ctx);
}