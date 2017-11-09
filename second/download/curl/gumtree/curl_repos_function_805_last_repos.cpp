static int MD5_Init(MD5_CTX *pctx)
{
  return nss_hash_init(pctx, SEC_OID_MD5);
}