{
    ccp = curl_maprintf("%lx", version);
    if(!ccp)
      return CURLE_OUT_OF_MEMORY;
    Curl_ssl_push_certinfo(data, certnum, "Version", ccp);
    free((char *) ccp);
  }