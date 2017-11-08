CURLcode Curl_output_digest(struct connectdata *conn,
                            bool proxy,
                            const unsigned char *request,
                            const unsigned char *uripath)
{
  /* We have a Digest setup for this, use it!  Now, to get all the details for
     this sorted out, I must urge you dear friend to read up on the RFC2617
     section 3.2.2, */
  unsigned char md5buf[16]; /* 16 bytes/128 bits */
  unsigned char request_digest[33];
  unsigned char *md5this;
  unsigned char *ha1;
  unsigned char ha2[33];/* 32 digits and 1 zero byte */
  char cnoncebuf[7];
  char *cnonce;
  char *tmp = NULL;
  struct timeval now;

  char **allocuserpwd;
  char *userp;
  char *passwdp;
  struct auth *authp;

  struct SessionHandle *data = conn->data;
  struct digestdata *d;
#ifdef CURL_DOES_CONVERSIONS
  CURLcode rc;
/* The CURL_OUTPUT_DIGEST_CONV macro below is for non-ASCII machines.
   It converts digest text to ASCII so the MD5 will be correct for 
   what ultimately goes over the network.
*/
#define CURL_OUTPUT_DIGEST_CONV(a, b) \
  rc = Curl_convert_to_network(a, (char *)b, strlen((const char*)b)); \
  if(rc != CURLE_OK) { \
    free(b); \
    return rc; \
  }
#else
#define CURL_OUTPUT_DIGEST_CONV(a, b)
#endif /* CURL_DOES_CONVERSIONS */

  if(proxy) {
    d = &data->state.proxydigest;
    allocuserpwd = &conn->allocptr.proxyuserpwd;
    userp = conn->proxyuser;
    passwdp = conn->proxypasswd;
    authp = &data->state.authproxy;
  }
  else {
    d = &data->state.digest;
    allocuserpwd = &conn->allocptr.userpwd;
    userp = conn->user;
    passwdp = conn->passwd;
    authp = &data->state.authhost;
  }

  if(*allocuserpwd) {
    Curl_safefree(*allocuserpwd);
    *allocuserpwd = NULL;
  }

  /* not set means empty */
  if(!userp)
    userp=(char *)"";

  if(!passwdp)
    passwdp=(char *)"";

  if(!d->nonce) {
    authp->done = FALSE;
    return CURLE_OK;
  }
  authp->done = TRUE;

  if(!d->nc)
    d->nc = 1;

  if(!d->cnonce) {
    /* Generate a cnonce */
    now = Curl_tvnow();
    snprintf(cnoncebuf, sizeof(cnoncebuf), "%06ld", now.tv_sec);
    if(Curl_base64_encode(data, cnoncebuf, strlen(cnoncebuf), &cnonce))
      d->cnonce = cnonce;
    else
      return CURLE_OUT_OF_MEMORY;
  }

  /*
    if the algorithm is "MD5" or unspecified (which then defaults to MD5):

    A1 = unq(username-value) ":" unq(realm-value) ":" passwd

    if the algorithm is "MD5-sess" then:

    A1 = H( unq(username-value) ":" unq(realm-value) ":" passwd )
         ":" unq(nonce-value) ":" unq(cnonce-value)
  */

  md5this = (unsigned char *)
    aprintf("%s:%s:%s", userp, d->realm, passwdp);
  if(!md5this)
    return CURLE_OUT_OF_MEMORY;

  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
  Curl_md5it(md5buf, md5this);
  free(md5this); /* free this again */

  ha1 = (unsigned char *)malloc(33); /* 32 digits and 1 zero byte */
  if(!ha1)
    return CURLE_OUT_OF_MEMORY;

  md5_to_ascii(md5buf, ha1);

  if(d->algo == CURLDIGESTALGO_MD5SESS) {
    /* nonce and cnonce are OUTSIDE the hash */
    tmp = aprintf("%s:%s:%s", ha1, d->nonce, d->cnonce);
    if(!tmp)
      return CURLE_OUT_OF_MEMORY;
    CURL_OUTPUT_DIGEST_CONV(data, tmp); /* convert on non-ASCII machines */
    Curl_md5it(md5buf, (unsigned char *)tmp);
    free(tmp); /* free this again */
    md5_to_ascii(md5buf, ha1);
  }

  /*
    If the "qop" directive's value is "auth" or is unspecified, then A2 is:

      A2       = Method ":" digest-uri-value

          If the "qop" value is "auth-int", then A2 is:

      A2       = Method ":" digest-uri-value ":" H(entity-body)

    (The "Method" value is the HTTP request method as specified in section
    5.1.1 of RFC 2616)
  */

  md5this = (unsigned char *)aprintf("%s:%s", request, uripath);
  if(!md5this) {
    free(ha1);
    return CURLE_OUT_OF_MEMORY;
  }

  if(d->qop && strequal(d->qop, "auth-int")) {
    /* We don't support auth-int at the moment. I can't see a easy way to get
       entity-body here */
    /* TODO: Append H(entity-body)*/
  }
  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
  Curl_md5it(md5buf, md5this);
  free(md5this); /* free this again */
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
  free(ha1);
  if(!md5this)
    return CURLE_OUT_OF_MEMORY;

  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
  Curl_md5it(md5buf, md5this);
  free(md5this); /* free this again */
  md5_to_ascii(md5buf, request_digest);

  /* for test case 64 (snooped from a Mozilla 1.3a request)

    Authorization: Digest username="testuser", realm="testrealm", \
    nonce="1053604145", uri="/64", response="c55f7f30d83d774a3d2dcacf725abaca"
  */

  if(d->qop) {
    *allocuserpwd =
      aprintf( "%sAuthorization: Digest "
               "username=\"%s\", "
               "realm=\"%s\", "
               "nonce=\"%s\", "
               "uri=\"%s\", "
               "cnonce=\"%s\", "
               "nc=%08x, "
               "qop=\"%s\", "
               "response=\"%s\"",
               proxy?"Proxy-":"",
               userp,
               d->realm,
               d->nonce,
               uripath, /* this is the PATH part of the URL */
               d->cnonce,
               d->nc,
               d->qop,
               request_digest);

    if(strequal(d->qop, "auth"))
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
               "uri=\"%s\", "
               "response=\"%s\"",
               proxy?"Proxy-":"",
               userp,
               d->realm,
               d->nonce,
               uripath, /* this is the PATH part of the URL */
               request_digest);
  }
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

  /* append CRLF to the userpwd header */
  tmp = (char*) realloc(*allocuserpwd, strlen(*allocuserpwd) + 3 + 1);
  if(!tmp)
    return CURLE_OUT_OF_MEMORY;
  strcat(tmp, "\r\n");
  *allocuserpwd = tmp;

  return CURLE_OK;
}