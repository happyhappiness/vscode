CURLcode Curl_auth_decode_digest_http_message(const char *chlg,
                                              struct digestdata *digest)
{
  size_t chlglen = strlen(chlg);

  /* We had an input token before so if there's another one now that means we
     provided bad credentials in the previous request or it's stale. */
  if(digest->input_token) {
    bool stale = false;
    const char *p = chlg;

    /* Check for the 'stale' directive */
    for(;;) {
      char value[DIGEST_MAX_VALUE_LENGTH];
      char content[DIGEST_MAX_CONTENT_LENGTH];

      while(*p && ISSPACE(*p))
        p++;

      if(!Curl_auth_digest_get_pair(p, value, content, &p))
        break;

      if(strcasecompare(value, "stale") &&
         strcasecompare(content, "true")) {
        stale = true;
        break;
      }

      while(*p && ISSPACE(*p))
        p++;

      if(',' == *p)
        p++;
    }

    if(stale)
      Curl_auth_digest_cleanup(digest);
    else
      return CURLE_LOGIN_DENIED;
  }

  /* Store the challenge for use later */
  digest->input_token = (BYTE *) Curl_memdup(chlg, chlglen + 1);
  if(!digest->input_token)
    return CURLE_OUT_OF_MEMORY;

  digest->input_token_len = chlglen;

  return CURLE_OK;
}