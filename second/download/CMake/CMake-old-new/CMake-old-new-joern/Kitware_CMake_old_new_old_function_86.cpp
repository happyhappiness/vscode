CURLcode Curl_auth_create_digest_http_message(struct Curl_easy *data,
                                              const char *userp,
                                              const char *passwdp,
                                              const unsigned char *request,
                                              const unsigned char *uripath,
                                              struct digestdata *digest,
                                              char **outptr, size_t *outlen)
{
  CURLcode result;
  unsigned char md5buf[16]; /* 16 bytes/128 bits */
  unsigned char request_digest[33];
  unsigned char *md5this;
  unsigned char ha1[33];    /* 32 digits and 1 zero byte */
  unsigned char ha2[33];    /* 32 digits and 1 zero byte */
  char cnoncebuf[33];
  char *cnonce = NULL;
  size_t cnonce_sz = 0;
  char *userp_quoted;
  char *response = NULL;
  char *tmp = NULL;

  if(!digest->nc)
    digest->nc = 1;

  if(!digest->cnonce) {
    unsigned int rnd[4];
    result = Curl_rand(data, &rnd[0], 4);
    if(result)
      return result;
    snprintf(cnoncebuf, sizeof(cnoncebuf), "%08x%08x%08x%08x",
             rnd[0], rnd[1], rnd[2], rnd[3]);

    result = Curl_base64_encode(data, cnoncebuf, strlen(cnoncebuf),
                                &cnonce, &cnonce_sz);
    if(result)
      return result;

    digest->cnonce = cnonce;
  }

  /*
    If the algorithm is "MD5" or unspecified (which then defaults to MD5):

      A1 = unq(username-value) ":" unq(realm-value) ":" passwd

    If the algorithm is "MD5-sess" then:

      A1 = H(unq(username-value) ":" unq(realm-value) ":" passwd) ":"
           unq(nonce-value) ":" unq(cnonce-value)
  */

  md5this = (unsigned char *)
    aprintf("%s:%s:%s", userp, digest->realm, passwdp);
  if(!md5this)
    return CURLE_OUT_OF_MEMORY;

  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
  Curl_md5it(md5buf, md5this);
  free(md5this);
  auth_digest_md5_to_ascii(md5buf, ha1);

  if(digest->algo == CURLDIGESTALGO_MD5SESS) {
    /* nonce and cnonce are OUTSIDE the hash */
    tmp = aprintf("%s:%s:%s", ha1, digest->nonce, digest->cnonce);
    if(!tmp)
      return CURLE_OUT_OF_MEMORY;

    CURL_OUTPUT_DIGEST_CONV(data, tmp); /* Convert on non-ASCII machines */
    Curl_md5it(md5buf, (unsigned char *) tmp);
    free(tmp);
    auth_digest_md5_to_ascii(md5buf, ha1);
  }

  /*
    If the "qop" directive's value is "auth" or is unspecified, then A2 is:

      A2 = Method ":" digest-uri-value

    If the "qop" value is "auth-int", then A2 is:

      A2 = Method ":" digest-uri-value ":" H(entity-body)

    (The "Method" value is the HTTP request method as specified in section
    5.1.1 of RFC 2616)
  */

  md5this = (unsigned char *) aprintf("%s:%s", request, uripath);

  if(digest->qop && strcasecompare(digest->qop, "auth-int")) {
    /* We don't support auth-int for PUT or POST at the moment.
       TODO: replace md5 of empty string with entity-body for PUT/POST */
    unsigned char *md5this2 = (unsigned char *)
      aprintf("%s:%s", md5this, "d41d8cd98f00b204e9800998ecf8427e");
    free(md5this);
    md5this = md5this2;
  }

  if(!md5this)
    return CURLE_OUT_OF_MEMORY;

  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
  Curl_md5it(md5buf, md5this);
  free(md5this);
  auth_digest_md5_to_ascii(md5buf, ha2);

  if(digest->qop) {
    md5this = (unsigned char *) aprintf("%s:%s:%08x:%s:%s:%s",
                                        ha1,
                                        digest->nonce,
                                        digest->nc,
                                        digest->cnonce,
                                        digest->qop,
                                        ha2);
  }
  else {
    md5this = (unsigned char *) aprintf("%s:%s:%s",
                                        ha1,
                                        digest->nonce,
                                        ha2);
  }

  if(!md5this)
    return CURLE_OUT_OF_MEMORY;

  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
  Curl_md5it(md5buf, md5this);
  free(md5this);
  auth_digest_md5_to_ascii(md5buf, request_digest);

  /* For test case 64 (snooped from a Mozilla 1.3a request)

     Authorization: Digest username="testuser", realm="testrealm", \
     nonce="1053604145", uri="/64", response="c55f7f30d83d774a3d2dcacf725abaca"

     Digest parameters are all quoted strings.  Username which is provided by
     the user will need double quotes and backslashes within it escaped.  For
     the other fields, this shouldn't be an issue.  realm, nonce, and opaque
     are copied as is from the server, escapes and all.  cnonce is generated
     with web-safe characters.  uri is already percent encoded.  nc is 8 hex
     characters.  algorithm and qop with standard values only contain web-safe
     characters.
  */
  userp_quoted = auth_digest_string_quoted(userp);
  if(!userp_quoted)
    return CURLE_OUT_OF_MEMORY;

  if(digest->qop) {
    response = aprintf("username=\"%s\", "
                       "realm=\"%s\", "
                       "nonce=\"%s\", "
                       "uri=\"%s\", "
                       "cnonce=\"%s\", "
                       "nc=%08x, "
                       "qop=%s, "
                       "response=\"%s\"",
                       userp_quoted,
                       digest->realm,
                       digest->nonce,
                       uripath,
                       digest->cnonce,
                       digest->nc,
                       digest->qop,
                       request_digest);

    if(strcasecompare(digest->qop, "auth"))
      digest->nc++; /* The nc (from RFC) has to be a 8 hex digit number 0
                       padded which tells to the server how many times you are
                       using the same nonce in the qop=auth mode */
  }
  else {
    response = aprintf("username=\"%s\", "
                       "realm=\"%s\", "
                       "nonce=\"%s\", "
                       "uri=\"%s\", "
                       "response=\"%s\"",
                       userp_quoted,
                       digest->realm,
                       digest->nonce,
                       uripath,
                       request_digest);
  }
  free(userp_quoted);
  if(!response)
    return CURLE_OUT_OF_MEMORY;

  /* Add the optional fields */
  if(digest->opaque) {
    /* Append the opaque */
    tmp = aprintf("%s, opaque=\"%s\"", response, digest->opaque);
    free(response);
    if(!tmp)
      return CURLE_OUT_OF_MEMORY;

    response = tmp;
  }

  if(digest->algorithm) {
    /* Append the algorithm */
    tmp = aprintf("%s, algorithm=\"%s\"", response, digest->algorithm);
    free(response);
    if(!tmp)
      return CURLE_OUT_OF_MEMORY;

    response = tmp;
  }

  /* Return the output */
  *outptr = response;
  *outlen = strlen(response);

  return CURLE_OK;
}