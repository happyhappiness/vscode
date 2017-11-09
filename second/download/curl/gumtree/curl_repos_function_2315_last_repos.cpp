CURLcode Curl_auth_decode_cram_md5_message(const char *chlg64, char **outptr,
                                           size_t *outlen)
{
  CURLcode result = CURLE_OK;
  size_t chlg64len = strlen(chlg64);

  *outptr = NULL;
  *outlen = 0;

  /* Decode the challenge if necessary */
  if(chlg64len && *chlg64 != '=')
    result = Curl_base64_decode(chlg64, (unsigned char **) outptr, outlen);

  return result;
}