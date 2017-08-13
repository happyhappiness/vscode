CURLcode Curl_auth_create_cram_md5_message(struct Curl_easy *data,
                                           const char *chlg,
                                           const char *userp,
                                           const char *passwdp,
                                           char **outptr, size_t *outlen)
{
  CURLcode result = CURLE_OK;
  size_t chlglen = 0;
  HMAC_context *ctxt;
  unsigned char digest[MD5_DIGEST_LEN];
  char *response;

  if(chlg)
    chlglen = strlen(chlg);

  /* Compute the digest using the password as the key */
  ctxt = Curl_HMAC_init(Curl_HMAC_MD5,
                        (const unsigned char *) passwdp,
                        curlx_uztoui(strlen(passwdp)));
  if(!ctxt)
    return CURLE_OUT_OF_MEMORY;

  /* Update the digest with the given challenge */
  if(chlglen > 0)
    Curl_HMAC_update(ctxt, (const unsigned char *) chlg,
                     curlx_uztoui(chlglen));

  /* Finalise the digest */
  Curl_HMAC_final(ctxt, digest);

  /* Generate the response */
  response = aprintf(
    "%s %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
    userp, digest[0], digest[1], digest[2], digest[3], digest[4],
    digest[5], digest[6], digest[7], digest[8], digest[9], digest[10],
    digest[11], digest[12], digest[13], digest[14], digest[15]);
  if(!response)
    return CURLE_OUT_OF_MEMORY;

  /* Base64 encode the response */
  result = Curl_base64_encode(data, response, 0, outptr, outlen);

  free(response);

  return result;
}