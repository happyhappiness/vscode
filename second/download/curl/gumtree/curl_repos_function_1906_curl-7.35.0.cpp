CURLdigest Curl_input_digest(struct connectdata *conn,
                             bool proxy,
                             const char *header) /* rest of the *-authenticate:
                                                    header */
{
  char *token = NULL;
  char *tmp = NULL;
  bool foundAuth = FALSE;
  bool foundAuthInt = FALSE;
  struct SessionHandle *data=conn->data;
  bool before = FALSE; /* got a nonce before */
  struct digestdata *d;

  if(proxy) {
    d = &data->state.proxydigest;
  }
  else {
    d = &data->state.digest;
  }

  if(checkprefix("Digest", header)) {
    header += strlen("Digest");

    /* If we already have received a nonce, keep that in mind */
    if(d->nonce)
      before = TRUE;

    /* clear off any former leftovers and init to defaults */
    digest_cleanup_one(d);

    for(;;) {
      char value[MAX_VALUE_LENGTH];
      char content[MAX_CONTENT_LENGTH];

      while(*header && ISSPACE(*header))
        header++;

      /* extract a value=content pair */
      if(!get_pair(header, value, content, &header)) {
        if(Curl_raw_equal(value, "nonce")) {
          d->nonce = strdup(content);
          if(!d->nonce)
            return CURLDIGEST_NOMEM;
        }
        else if(Curl_raw_equal(value, "stale")) {
          if(Curl_raw_equal(content, "true")) {
            d->stale = TRUE;
            d->nc = 1; /* we make a new nonce now */
          }
        }
        else if(Curl_raw_equal(value, "realm")) {
          d->realm = strdup(content);
          if(!d->realm)
            return CURLDIGEST_NOMEM;
        }
        else if(Curl_raw_equal(value, "opaque")) {
          d->opaque = strdup(content);
          if(!d->opaque)
            return CURLDIGEST_NOMEM;
        }
        else if(Curl_raw_equal(value, "qop")) {
          char *tok_buf;
          /* tokenize the list and choose auth if possible, use a temporary
             clone of the buffer since strtok_r() ruins it */
          tmp = strdup(content);
          if(!tmp)
            return CURLDIGEST_NOMEM;
          token = strtok_r(tmp, ",", &tok_buf);
          while(token != NULL) {
            if(Curl_raw_equal(token, "auth")) {
              foundAuth = TRUE;
            }
            else if(Curl_raw_equal(token, "auth-int")) {
              foundAuthInt = TRUE;
            }
            token = strtok_r(NULL, ",", &tok_buf);
          }
          free(tmp);
          /*select only auth o auth-int. Otherwise, ignore*/
          if(foundAuth) {
            d->qop = strdup("auth");
            if(!d->qop)
              return CURLDIGEST_NOMEM;
          }
          else if(foundAuthInt) {
            d->qop = strdup("auth-int");
            if(!d->qop)
              return CURLDIGEST_NOMEM;
          }
        }
        else if(Curl_raw_equal(value, "algorithm")) {
          d->algorithm = strdup(content);
          if(!d->algorithm)
            return CURLDIGEST_NOMEM;
          if(Curl_raw_equal(content, "MD5-sess"))
            d->algo = CURLDIGESTALGO_MD5SESS;
          else if(Curl_raw_equal(content, "MD5"))
            d->algo = CURLDIGESTALGO_MD5;
          else
            return CURLDIGEST_BADALGO;
        }
        else {
          /* unknown specifier, ignore it! */
        }
      }
      else
        break; /* we're done here */

      /* pass all additional spaces here */
      while(*header && ISSPACE(*header))
        header++;
      if(',' == *header)
        /* allow the list to be comma-separated */
        header++;
    }
    /* We had a nonce since before, and we got another one now without
       'stale=true'. This means we provided bad credentials in the previous
       request */
    if(before && !d->stale)
      return CURLDIGEST_BAD;

    /* We got this header without a nonce, that's a bad Digest line! */
    if(!d->nonce)
      return CURLDIGEST_BAD;
  }
  else
    /* else not a digest, get out */
    return CURLDIGEST_NONE;

  return CURLDIGEST_FINE;
}