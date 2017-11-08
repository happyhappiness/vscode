static void SHA256_Update(SHA256_CTX *ctx,
                          const unsigned char *input,
                          unsigned int inputLen)
{
  sha256_update(ctx, inputLen, input);
}