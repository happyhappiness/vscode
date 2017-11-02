CURLcode Curl_hmac_md5(const unsigned char *key, unsigned int keylen,
                       const unsigned char *data, unsigned int datalen,
                       unsigned char *output)
{
  HMAC_context *ctxt = Curl_HMAC_init(Curl_HMAC_MD5, key, keylen);

  if(!ctxt)
    return CURLE_OUT_OF_MEMORY;

  /* Update the digest with the given challenge */
  Curl_HMAC_update(ctxt, data, datalen);

  /* Finalise the digest */
  Curl_HMAC_final(ctxt, output);

  return CURLE_OK;
}