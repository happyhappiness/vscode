static void MD5_Final(unsigned char digest[16], MD5_CTX * ctx)
{
  md5_digest(ctx, 16, digest);
}