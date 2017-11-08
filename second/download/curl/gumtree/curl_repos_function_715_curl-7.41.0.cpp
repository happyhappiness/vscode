static void SHA1_Update(SHA_CTX *ctx,
                        const unsigned char *input,
                        unsigned int inputLen)
{
  CryptHashData(ctx->hHash, (unsigned char *)input, inputLen, 0);
}