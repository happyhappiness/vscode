{
    md5this = (unsigned char *)aprintf("%s:%s:%s",
                                       ha1,
                                       d->nonce,
                                       ha2);
  }