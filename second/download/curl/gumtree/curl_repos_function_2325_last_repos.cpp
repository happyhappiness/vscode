CURLcode Curl_auth_decode_digest_http_message(const char *chlg,
                                              struct digestdata *digest)
{
  bool before = FALSE; /* got a nonce before */
  bool foundAuth = FALSE;
  bool foundAuthInt = FALSE;
  char *token = NULL;
  char *tmp = NULL;

  /* If we already have received a nonce, keep that in mind */
  if(digest->nonce)
    before = TRUE;

  /* Clean up any former leftovers and initialise to defaults */
  Curl_auth_digest_cleanup(digest);

  for(;;) {
    char value[DIGEST_MAX_VALUE_LENGTH];
    char content[DIGEST_MAX_CONTENT_LENGTH];

    /* Pass all additional spaces here */
    while(*chlg && ISSPACE(*chlg))
      chlg++;

    /* Extract a value=content pair */
    if(Curl_auth_digest_get_pair(chlg, value, content, &chlg)) {
      if(strcasecompare(value, "nonce")) {
        free(digest->nonce);
        digest->nonce = strdup(content);
        if(!digest->nonce)
          return CURLE_OUT_OF_MEMORY;
      }
      else if(strcasecompare(value, "stale")) {
        if(strcasecompare(content, "true")) {
          digest->stale = TRUE;
          digest->nc = 1; /* we make a new nonce now */
        }
      }
      else if(strcasecompare(value, "realm")) {
        free(digest->realm);
        digest->realm = strdup(content);
        if(!digest->realm)
          return CURLE_OUT_OF_MEMORY;
      }
      else if(strcasecompare(value, "opaque")) {
        free(digest->opaque);
        digest->opaque = strdup(content);
        if(!digest->opaque)
          return CURLE_OUT_OF_MEMORY;
      }
      else if(strcasecompare(value, "qop")) {
        char *tok_buf = NULL;
        /* Tokenize the list and choose auth if possible, use a temporary
           clone of the buffer since strtok_r() ruins it */
        tmp = strdup(content);
        if(!tmp)
          return CURLE_OUT_OF_MEMORY;

        token = strtok_r(tmp, ",", &tok_buf);
        while(token != NULL) {
          if(strcasecompare(token, DIGEST_QOP_VALUE_STRING_AUTH)) {
            foundAuth = TRUE;
          }
          else if(strcasecompare(token, DIGEST_QOP_VALUE_STRING_AUTH_INT)) {
            foundAuthInt = TRUE;
          }
          token = strtok_r(NULL, ",", &tok_buf);
        }

        free(tmp);

        /* Select only auth or auth-int. Otherwise, ignore */
        if(foundAuth) {
          free(digest->qop);
          digest->qop = strdup(DIGEST_QOP_VALUE_STRING_AUTH);
          if(!digest->qop)
            return CURLE_OUT_OF_MEMORY;
        }
        else if(foundAuthInt) {
          free(digest->qop);
          digest->qop = strdup(DIGEST_QOP_VALUE_STRING_AUTH_INT);
          if(!digest->qop)
            return CURLE_OUT_OF_MEMORY;
        }
      }
      else if(strcasecompare(value, "algorithm")) {
        free(digest->algorithm);
        digest->algorithm = strdup(content);
        if(!digest->algorithm)
          return CURLE_OUT_OF_MEMORY;

        if(strcasecompare(content, "MD5-sess"))
          digest->algo = CURLDIGESTALGO_MD5SESS;
        else if(strcasecompare(content, "MD5"))
          digest->algo = CURLDIGESTALGO_MD5;
        else
          return CURLE_BAD_CONTENT_ENCODING;
      }
      else {
        /* Unknown specifier, ignore it! */
      }
    }
    else
      break; /* We're done here */

    /* Pass all additional spaces here */
    while(*chlg && ISSPACE(*chlg))
      chlg++;

    /* Allow the list to be comma-separated */
    if(',' == *chlg)
      chlg++;
  }

  /* We had a nonce since before, and we got another one now without
     'stale=true'. This means we provided bad credentials in the previous
     request */
  if(before && !digest->stale)
    return CURLE_BAD_CONTENT_ENCODING;

  /* We got this header without a nonce, that's a bad Digest line! */
  if(!digest->nonce)
    return CURLE_BAD_CONTENT_ENCODING;

  return CURLE_OK;
}