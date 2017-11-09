static int nss_hash_init(void **pctx, SECOidTag hash_alg)
{
  PK11Context *ctx;

  /* we have to initialize NSS if not initialized alraedy */
  if(!NSS_IsInitialized() && !nss_context) {
    static NSSInitParameters params;
    params.length = sizeof params;
    nss_context = NSS_InitContext("", "", "", "", &params, NSS_INIT_READONLY
        | NSS_INIT_NOCERTDB   | NSS_INIT_NOMODDB       | NSS_INIT_FORCEOPEN
        | NSS_INIT_NOROOTINIT | NSS_INIT_OPTIMIZESPACE | NSS_INIT_PK11RELOAD);
  }

  ctx = PK11_CreateDigestContext(hash_alg);
  if(!ctx)
    return /* failure */ 0;

  if(PK11_DigestBegin(ctx) != SECSuccess) {
    PK11_DestroyContext(ctx, PR_TRUE);
    return /* failure */ 0;
  }

  *pctx = ctx;
  return /* success */ 1;
}