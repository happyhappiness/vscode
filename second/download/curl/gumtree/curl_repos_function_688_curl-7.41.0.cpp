static void SHA256_Update(SHA256_CTX *ctx,
                          const unsigned char *input,
                          unsigned int inputLen)
{
  gcry_md_write(*ctx, input, inputLen);
}