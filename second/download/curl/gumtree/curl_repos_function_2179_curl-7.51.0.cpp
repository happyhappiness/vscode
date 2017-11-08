CURLcode Curl_auth_decode_ntlm_type2_message(struct Curl_easy *data,
                                             const char *type2msg,
                                             struct ntlmdata *ntlm)
{
  CURLcode result = CURLE_OK;
  unsigned char *type2 = NULL;
  size_t type2_len = 0;

#if defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void) data;
#endif

  /* Decode the base-64 encoded type-2 message */
  if(strlen(type2msg) && *type2msg != '=') {
    result = Curl_base64_decode(type2msg, &type2, &type2_len);
    if(result)
      return result;
  }

  /* Ensure we have a valid type-2 message */
  if(!type2) {
    infof(data, "NTLM handshake failure (empty type-2 message)\n");

    return CURLE_BAD_CONTENT_ENCODING;
  }

  /* Simply store the challenge for use later */
  ntlm->input_token = type2;
  ntlm->input_token_len = type2_len;

  return result;
}