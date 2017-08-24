{
    (*hashparams->hmac_hinit)(ctxt->hmac_hashctxt1);
    (*hashparams->hmac_hupdate)(ctxt->hmac_hashctxt1, key, keylen);
    hkey = (unsigned char *) ctxt->hmac_hashctxt2 + hashparams->hmac_ctxtsize;
    (*hashparams->hmac_hfinal)(hkey, ctxt->hmac_hashctxt1);
    key = hkey;
    keylen = hashparams->hmac_resultlen;
  }