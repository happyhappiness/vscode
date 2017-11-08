static void SHA1_Update(SHA_CTX *pctx,
                        const unsigned char *input,
                        unsigned int input_len)
{
  PK11_DigestOp(*pctx, input, input_len);
}