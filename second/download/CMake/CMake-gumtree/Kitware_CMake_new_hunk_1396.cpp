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

