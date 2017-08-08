{
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

    if(Curl_raw_equal(digest->qop, "auth"))
      digest->nc++; /* The nc (from RFC) has to be a 8 hex digit number 0
                       padded which tells to the server how many times you are
                       using the same nonce in the qop=auth mode */
  }