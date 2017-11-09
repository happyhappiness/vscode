static void MD5_Final(unsigned char digest[16], MD5_CTX * ctx)
{
  memcpy(digest, gcry_md_read(*ctx, 0), 16);
  gcry_md_close(*ctx);
}