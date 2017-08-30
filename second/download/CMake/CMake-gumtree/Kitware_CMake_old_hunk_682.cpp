     http://www.fngtps.com/2006/09/http-authentication
  */

  if(authp->iestyle && ((tmp = strchr((char *)uripath, '?')) != NULL))
    urilen = tmp - (char *)uripath;
  else
    urilen = strlen((char *)uripath);

  md5this = (unsigned char *)aprintf("%s:%.*s", request, urilen, uripath);

  if(d->qop && Curl_raw_equal(d->qop, "auth-int")) {
    /* We don't support auth-int for PUT or POST at the moment.
       TODO: replace md5 of empty string with entity-body for PUT/POST */
    unsigned char *md5this2 = (unsigned char *)
      aprintf("%s:%s", md5this, "d41d8cd98f00b204e9800998ecf8427e");
    Curl_safefree(md5this);
    md5this = md5this2;
  }

  if(!md5this)
    return CURLE_OUT_OF_MEMORY;

  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
  Curl_md5it(md5buf, md5this);
  Curl_safefree(md5this);
  md5_to_ascii(md5buf, ha2);

  if(d->qop) {
    md5this = (unsigned char *)aprintf("%s:%s:%08x:%s:%s:%s",
                                       ha1,
                                       d->nonce,
                                       d->nc,
                                       d->cnonce,
                                       d->qop,
                                       ha2);
  }
  else {
    md5this = (unsigned char *)aprintf("%s:%s:%s",
                                       ha1,
                                       d->nonce,
                                       ha2);
  }
  if(!md5this)
    return CURLE_OUT_OF_MEMORY;

  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
  Curl_md5it(md5buf, md5this);
  Curl_safefree(md5this);
  md5_to_ascii(md5buf, request_digest);

  /* for test case 64 (snooped from a Mozilla 1.3a request)

    Authorization: Digest username="testuser", realm="testrealm", \
    nonce="1053604145", uri="/64", response="c55f7f30d83d774a3d2dcacf725abaca"

    Digest parameters are all quoted strings.  Username which is provided by
    the user will need double quotes and backslashes within it escaped.  For
    the other fields, this shouldn't be an issue.  realm, nonce, and opaque
    are copied as is from the server, escapes and all.  cnonce is generated
    with web-safe characters.  uri is already percent encoded.  nc is 8 hex
    characters.  algorithm and qop with standard values only contain web-safe
    chracters.
  */
  userp_quoted = string_quoted(userp);
  if(!userp_quoted)
    return CURLE_OUT_OF_MEMORY;

  if(d->qop) {
    *allocuserpwd =
      aprintf( "%sAuthorization: Digest "
               "username=\"%s\", "
               "realm=\"%s\", "
               "nonce=\"%s\", "
               "uri=\"%.*s\", "
               "cnonce=\"%s\", "
               "nc=%08x, "
               "qop=%s, "
               "response=\"%s\"",
               proxy?"Proxy-":"",
               userp_quoted,
               d->realm,
               d->nonce,
               urilen, uripath, /* this is the PATH part of the URL */
               d->cnonce,
               d->nc,
               d->qop,
               request_digest);

    if(Curl_raw_equal(d->qop, "auth"))
      d->nc++; /* The nc (from RFC) has to be a 8 hex digit number 0 padded
                  which tells to the server how many times you are using the
                  same nonce in the qop=auth mode. */
  }
  else {
    *allocuserpwd =
      aprintf( "%sAuthorization: Digest "
               "username=\"%s\", "
               "realm=\"%s\", "
               "nonce=\"%s\", "
               "uri=\"%.*s\", "
               "response=\"%s\"",
               proxy?"Proxy-":"",
               userp_quoted,
               d->realm,
               d->nonce,
               urilen, uripath, /* this is the PATH part of the URL */
               request_digest);
  }
  Curl_safefree(userp_quoted);
  if(!*allocuserpwd)
    return CURLE_OUT_OF_MEMORY;

  /* Add optional fields */
  if(d->opaque) {
    /* append opaque */
    tmp = aprintf("%s, opaque=\"%s\"", *allocuserpwd, d->opaque);
    if(!tmp)
      return CURLE_OUT_OF_MEMORY;
    free(*allocuserpwd);
    *allocuserpwd = tmp;
  }

  if(d->algorithm) {
    /* append algorithm */
    tmp = aprintf("%s, algorithm=\"%s\"", *allocuserpwd, d->algorithm);
    if(!tmp)
      return CURLE_OUT_OF_MEMORY;
    free(*allocuserpwd);
    *allocuserpwd = tmp;
  }

  /* append CRLF + zero (3 bytes) to the userpwd header */
  userlen = strlen(*allocuserpwd);
  tmp = realloc(*allocuserpwd, userlen + 3);
  if(!tmp)
    return CURLE_OUT_OF_MEMORY;
  strcpy(&tmp[userlen], "\r\n"); /* append the data */
  *allocuserpwd = tmp;

  return CURLE_OK;
}

static void digest_cleanup_one(struct digestdata *d)
{
  Curl_safefree(d->nonce);
  Curl_safefree(d->cnonce);
  Curl_safefree(d->realm);
  Curl_safefree(d->opaque);
  Curl_safefree(d->qop);
  Curl_safefree(d->algorithm);

  d->nc = 0;
  d->algo = CURLDIGESTALGO_MD5; /* default algorithm */
  d->stale = FALSE; /* default means normal, not stale */
}


void Curl_digest_cleanup(struct SessionHandle *data)
{
  digest_cleanup_one(&data->state.digest);
  digest_cleanup_one(&data->state.proxydigest);
}

#endif