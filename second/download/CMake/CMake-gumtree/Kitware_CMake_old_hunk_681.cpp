

  /* not set means empty */

  if(!userp)

    userp="";



  if(!passwdp)

    passwdp="";



  if(!d->nonce) {

    authp->done = FALSE;

    return CURLE_OK;

  }

  authp->done = TRUE;



  if(!d->nc)

    d->nc = 1;



  if(!d->cnonce) {

    snprintf(cnoncebuf, sizeof(cnoncebuf), "%08x%08x%08x%08x",

             Curl_rand(data), Curl_rand(data),

             Curl_rand(data), Curl_rand(data));

    rc = Curl_base64_encode(data, cnoncebuf, strlen(cnoncebuf),

                            &cnonce, &cnonce_sz);

    if(rc)

      return rc;

    d->cnonce = cnonce;

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

  Curl_safefree(md5this);

  md5_to_ascii(md5buf, ha1);



  if(d->algo == CURLDIGESTALGO_MD5SESS) {

    /* nonce and cnonce are OUTSIDE the hash */

    tmp = aprintf("%s:%s:%s", ha1, d->nonce, d->cnonce);

    if(!tmp)

      return CURLE_OUT_OF_MEMORY;

    CURL_OUTPUT_DIGEST_CONV(data, tmp); /* convert on non-ASCII machines */

    Curl_md5it(md5buf, (unsigned char *)tmp);

    Curl_safefree(tmp);

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



  /* So IE browsers < v7 cut off the URI part at the query part when they

     evaluate the MD5 and some (IIS?) servers work with them so we may need to

