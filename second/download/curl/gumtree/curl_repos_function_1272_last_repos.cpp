void Curl_md4it(unsigned char *output, const unsigned char *input, size_t len)
{
  MD4_CTX ctx;
  MD4_Init(&ctx);
  MD4_Update(&ctx, input, curlx_uztoui(len));
  MD4_Final(output, &ctx);
}