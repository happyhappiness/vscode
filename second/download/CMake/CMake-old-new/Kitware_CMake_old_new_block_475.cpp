{
    snprintf(cnoncebuf, sizeof(cnoncebuf), "%08x%08x%08x%08x",
             Curl_rand(data), Curl_rand(data),
             Curl_rand(data), Curl_rand(data));
    rc = Curl_base64_encode(data, cnoncebuf, strlen(cnoncebuf),
                            &cnonce, &cnonce_sz);
    if(rc)
      return rc;
    d->cnonce = cnonce;
  }