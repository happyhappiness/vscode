static void MD5_Update(MD5_CTX *ctx,
                       const unsigned char *input,
                       unsigned int inputLen)
{
  CC_MD5_Update(ctx, input, inputLen);
}