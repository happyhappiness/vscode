{
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