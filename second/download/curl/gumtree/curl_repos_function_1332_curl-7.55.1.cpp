static CURLcode formboundary(struct Curl_easy *data,
                             char *buffer, size_t buflen)
{
  /* 24 dashes and 16 hexadecimal digits makes 64 bit (18446744073709551615)
     combinations */
  if(buflen < 41)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  memset(buffer, '-', 24);
  Curl_rand_hex(data, (unsigned char *)&buffer[24], 17);

  return CURLE_OK;
}