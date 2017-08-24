f(!ctxt->md5_hashctx) {
    free(ctxt);
    return NULL;
  }