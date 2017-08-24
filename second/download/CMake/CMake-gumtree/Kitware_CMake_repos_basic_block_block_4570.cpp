{
  MD5_context *ctxt;

  /* Create MD5 context */
  ctxt = malloc(sizeof *ctxt);

  if(!ctxt)
    return ctxt;

  ctxt->md5_hashctx = malloc(md5params->md5_ctxtsize);

  if(!ctxt->md5_hashctx) {
    free(ctxt);
    return NULL;
  }

  ctxt->md5_hash = md5params;

  (*md5params->md5_init_func)(ctxt->md5_hashctx);

  return ctxt;
}