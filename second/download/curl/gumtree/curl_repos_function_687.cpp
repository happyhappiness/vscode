static int SHA256_Init(SHA256_CTX *ctx)
{
  gcry_md_open(ctx, GCRY_MD_SHA256, 0);
  return 1;
}