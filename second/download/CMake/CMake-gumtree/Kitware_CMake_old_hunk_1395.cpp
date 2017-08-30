    aprintf("%s:%s:%s", userp, d->realm, passwdp);

  if(!md5this)

    return CURLE_OUT_OF_MEMORY;

  Curl_md5it(md5buf, md5this);

  free(md5this); /* free this again */



