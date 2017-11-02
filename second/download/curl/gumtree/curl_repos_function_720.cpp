digest_context *Curl_digest_init(const digest_params *dparams)
{
  digest_context *ctxt;

  /* Create digest context */
  ctxt = malloc(sizeof *ctxt);

  if(!ctxt)
    return ctxt;

  ctxt->digest_hashctx = malloc(dparams->digest_ctxtsize);

  if(!ctxt->digest_hashctx) {
    free(ctxt);
    return NULL;
  }

  ctxt->digest_hash = dparams;

  if(dparams->digest_init(ctxt->digest_hashctx) != 1) {
    free(ctxt);
    return NULL;
  }

  return ctxt;
}