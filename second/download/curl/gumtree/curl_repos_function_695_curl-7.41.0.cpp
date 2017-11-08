static int SHA1_Init(SHA_CTX *pctx)
{
  return nss_hash_init(pctx, SEC_OID_SHA1);
}