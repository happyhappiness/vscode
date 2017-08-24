{
    (*hashparams->hmac_hupdate)(ctxt->hmac_hashctxt1, &hmac_ipad, 1);
    (*hashparams->hmac_hupdate)(ctxt->hmac_hashctxt2, &hmac_opad, 1);
  }