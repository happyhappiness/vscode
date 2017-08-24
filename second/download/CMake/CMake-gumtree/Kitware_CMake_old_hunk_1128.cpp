  if(d->algo == CURLDIGESTALGO_MD5SESS) {
    /* nonce and cnonce are OUTSIDE the hash */
    tmp = aprintf("%s:%s:%s", ha1, d->nonce, d->cnonce);
    free(ha1);
    if(!tmp)
      return CURLE_OUT_OF_MEMORY;
    ha1 = (unsigned char *)tmp;
  }

  /*
