void Curl_md5it(unsigned char *outbuffer, /* 16 bytes */
                const unsigned char *input)
{
  MD5_CTX ctx;
  MD5_Init(&ctx);
  MD5_Update(&ctx, input, curlx_uztoui(strlen((char *)input)));
  MD5_Final(outbuffer, &ctx);
}