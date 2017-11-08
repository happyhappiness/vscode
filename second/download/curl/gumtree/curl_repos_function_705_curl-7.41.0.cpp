static void SHA1_Update(SHA_CTX *ctx,
                        const unsigned char *input,
                        unsigned int inputLen)
{
  sha1_update(ctx, input, inputLen);
}