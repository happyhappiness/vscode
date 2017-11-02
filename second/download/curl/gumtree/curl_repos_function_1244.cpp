static void MD5_Final(unsigned char digest[16], MD5_CTX *ctx)
{
  CC_MD5_Final(digest, ctx);
}