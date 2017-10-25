CURLdigest Curl_input_digest(struct connectdata *conn,
                             bool proxy,
                             char *header) /* rest of the *-authenticate:
                                              header */
{
  bool more = TRUE;
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

  /* skip initial whitespaces */
  while(*header && isspace((int)*header))
    header++;

  if(checkprefix("Digest", header)) {
    header += strlen("Digest");

    /* If we already have received a nonce, keep that in mind */
    if(d->nonce)
      before = TRUE;

    /* clear off any former leftovers and init to defaults */
    Curl_digest_cleanup_one(d);

    while(more) {
      char value[32];
      char content[128];
      size_t totlen=0;

      while(*header && isspace((int)*header))
        header++;

      /* how big can these strings be? */
      if((2 == sscanf(header, "%31[^=]=\"%127[^\"]\"",
                      value, content)) ||
         /* try the same scan but without quotes around the content but don't
            include the possibly trailing comma */
         (2 ==  sscanf(header, "%31[^=]=%127[^,]",
                       value, content)) ) {
        if(strequal(value, "nonce")) {
          d->nonce = strdup(content);
          if(!d->nonce)
            return CURLDIGEST_NOMEM;
        }
        else if(strequal(value, "stale")) {
          if(strequal(content, "true")) {
            d->stale = TRUE;
            d->nc = 1; /* we make a new nonce now */
          }
        }
        else if(strequal(value, "realm")) {
          d->realm = strdup(content);
          if(!d->realm)
            return CURLDIGEST_NOMEM;
        }
        else if(strequal(value, "opaque")) {
          d->opaque = strdup(content);
          if(!d->opaque)
            return CURLDIGEST_NOMEM;
        }
        else if(strequal(value, "qop")) {
          char *tok_buf;
          /* tokenize the list and choose auth if possible, use a temporary
             clone of the buffer since strtok_r() ruins it */
          tmp = strdup(content);
          if(!tmp)
            return CURLDIGEST_NOMEM;
          token = strtok_r(tmp, ",", &tok_buf);
          while (token != NULL) {
            if (strequal(token, "auth")) {
              foundAuth = TRUE;
            }
            else if (strequal(token, "auth-int")) {
              foundAuthInt = TRUE;
            }
            token = strtok_r(NULL, ",", &tok_buf);
          }
          free(tmp);
          /*select only auth o auth-int. Otherwise, ignore*/
          if (foundAuth) {
            d->qop = strdup("auth");
            if(!d->qop)
              return CURLDIGEST_NOMEM;
          }
          else if (foundAuthInt) {
            d->qop = strdup("auth-int");
            if(!d->qop)
              return CURLDIGEST_NOMEM;
          }
        }
        else if(strequal(value, "algorithm")) {
          d->algorithm = strdup(content);
          if(!d->algorithm)
            return CURLDIGEST_NOMEM;
          if(strequal(content, "MD5-sess"))
            d->algo = CURLDIGESTALGO_MD5SESS;
          else if(strequal(content, "MD5"))
            d->algo = CURLDIGESTALGO_MD5;
          else
            return CURLDIGEST_BADALGO;
        }
        else {
          /* unknown specifier, ignore it! */
        }
        totlen = strlen(value)+strlen(content)+1;

        if(header[strlen(value)+1] == '\"')
          /* the contents were within quotes, then add 2 for them to the
             length */
          totlen += 2;
      }
      else
        break; /* we're done here */

      header += totlen;
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