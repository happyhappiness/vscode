static int SHA1_Init(SHA_CTX *ctx)
{
  sha1_starts(ctx);
  return 1;
}