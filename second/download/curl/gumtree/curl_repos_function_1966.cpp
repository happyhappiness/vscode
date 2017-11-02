static CURLcode sasl_decode_digest_md5_message(const char *chlg64,
                                               char *nonce, size_t nlen,
                                               char *realm, size_t rlen,
                                               char *alg, size_t alen,
                                               char *qop, size_t qlen)
{
  CURLcode result = CURLE_OK;
  unsigned char *chlg = NULL;
  size_t chlglen = 0;
  size_t chlg64len = strlen(chlg64);

  /* Decode the base-64 encoded challenge message */
  if(chlg64len && *chlg64 != '=') {
    result = Curl_base64_decode(chlg64, &chlg, &chlglen);
    if(result)
      return result;
  }

  /* Ensure we have a valid challenge message */
  if(!chlg)
    return CURLE_BAD_CONTENT_ENCODING;

  /* Retrieve nonce string from the challenge */
  if(!sasl_digest_get_key_value((char *)chlg, "nonce=\"", nonce, nlen, '\"')) {
    Curl_safefree(chlg);
    return CURLE_BAD_CONTENT_ENCODING;
  }

  /* Retrieve realm string from the challenge */
  if(!sasl_digest_get_key_value((char *)chlg, "realm=\"", realm, rlen, '\"')) {
    /* Challenge does not have a realm, set empty string [RFC2831] page 6 */
    strcpy(realm, "");
  }

  /* Retrieve algorithm string from the challenge */
  if(!sasl_digest_get_key_value((char *)chlg, "algorithm=", alg, alen, ',')) {
    Curl_safefree(chlg);
    return CURLE_BAD_CONTENT_ENCODING;
  }

  /* Retrieve qop-options string from the challenge */
  if(!sasl_digest_get_key_value((char *)chlg, "qop=\"", qop, qlen, '\"')) {
    Curl_safefree(chlg);
    return CURLE_BAD_CONTENT_ENCODING;
  }

  Curl_safefree(chlg);

  return CURLE_OK;
}