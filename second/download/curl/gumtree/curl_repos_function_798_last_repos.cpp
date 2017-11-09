static void SHA1_Update(SHA_CTX *ctx,
                        const unsigned char *input,
                        unsigned int inputLen)
{
  gcry_md_write(*ctx, input, inputLen);
}