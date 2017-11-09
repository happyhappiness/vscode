static int SHA256_Init(SHA256_CTX *ctx)
{
  sha256_starts(ctx, 0); /* 0 = sha256 */
  return 1;
}