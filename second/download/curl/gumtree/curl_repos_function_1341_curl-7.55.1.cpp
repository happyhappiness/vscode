static void MD5_Update(MD5_CTX * ctx,
                       const unsigned char *input,
                       unsigned int inputLen)
{
  md5_update(ctx, inputLen, input);
}