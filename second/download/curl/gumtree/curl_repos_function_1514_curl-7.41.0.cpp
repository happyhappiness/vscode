CURLcode Curl_sasl_decode_digest_http_message(const char *chlg,
                                              struct digestdata *digest)
{
  size_t chlglen = strlen(chlg);

  /* We had an input token before and we got another one now. This means we
  provided bad credentials in the previous request. */
  if(digest->input_token)
    return CURLE_BAD_CONTENT_ENCODING;

  /* Simply store the challenge for use later */
  digest->input_token = (BYTE *) Curl_memdup(chlg, chlglen);
  if(!digest->input_token)
    return CURLE_OUT_OF_MEMORY;

  digest->input_token_len = chlglen;

  return CURLE_OK;
}