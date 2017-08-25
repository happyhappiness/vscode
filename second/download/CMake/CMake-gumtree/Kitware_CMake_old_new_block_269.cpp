{
    /* nonce and cnonce are OUTSIDE the hash */
    tmp = aprintf("%s:%s:%s", ha1, digest->nonce, digest->cnonce);
    if(!tmp)
      return CURLE_OUT_OF_MEMORY;

    CURL_OUTPUT_DIGEST_CONV(data, tmp); /* convert on non-ASCII machines */
    Curl_md5it(md5buf, (unsigned char *)tmp);
    free(tmp);
    sasl_digest_md5_to_ascii(md5buf, ha1);
  }