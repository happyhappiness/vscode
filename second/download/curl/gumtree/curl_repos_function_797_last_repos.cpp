static int SHA1_Init(SHA_CTX *ctx)
{
  gcry_md_open(ctx, GCRY_MD_SHA1, 0);
  return 1;
}