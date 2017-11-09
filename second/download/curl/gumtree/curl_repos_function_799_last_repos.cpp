static void SHA1_Final(unsigned char digest[20], SHA_CTX *ctx)
{
  memcpy(digest, gcry_md_read(*ctx, 0), 20);
  gcry_md_close(*ctx);
}