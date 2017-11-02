static void MD5_Update(MD5_CTX *ctx,
                       const unsigned char *input,
                       unsigned int inputLen)
{
  gcry_md_write(*ctx, input, inputLen);
}