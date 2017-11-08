static CURLcode mk_nt_hash(struct SessionHandle *data,
                           char *password,
                           unsigned char *ntbuffer /* 21 bytes */)
{
  size_t len = strlen(password);
  unsigned char *pw = malloc(len*2);
  if(!pw)
    return CURLE_OUT_OF_MEMORY;

  utf8_to_unicode_le(pw, password, len);

#ifdef CURL_DOES_CONVERSIONS
  /*
   * The NT hashed password needs to be created using the
   * password in the network encoding not the host encoding.
   */
  if(data)
    Curl_convert_to_network(data, (char *)pw, len*2);
#else
  (void)data;
#endif

  {
    /* Create NT hashed password. */
    MD4_CTX MD4pw;

    MD4_Init(&MD4pw);
    MD4_Update(&MD4pw, pw, 2*len);
    MD4_Final(ntbuffer, &MD4pw);

    memset(ntbuffer + 16, 0, 21 - 16);
  }

  free(pw);
  return CURLE_OK;
}