static int MD5_Init(MD5_CTX *ctx)
{
  md5_starts(ctx);
  return 1;
}