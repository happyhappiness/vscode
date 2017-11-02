static int SHA256_Init(SHA256_CTX *pctx)
{
  return nss_hash_init(pctx, SEC_OID_SHA256);
}