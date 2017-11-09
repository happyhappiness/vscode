static int SHA256_Init(SHA256_CTX *ctx)
{
  sha256_init(ctx);
  return 1;
}