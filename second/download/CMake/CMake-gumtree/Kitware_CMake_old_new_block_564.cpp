{
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