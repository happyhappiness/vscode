static void SHA1_Final(unsigned char digest[20], SHA_CTX *ctx)
{
  sha1_finish(ctx, digest);
}