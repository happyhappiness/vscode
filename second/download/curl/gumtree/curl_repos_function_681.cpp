static int MD5_Init(MD5_CTX *ctx)
{
  gcry_md_open(ctx, GCRY_MD_MD5, 0);
  return 1;
}