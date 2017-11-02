static void MD5_Final(unsigned char digest[16], MD5_CTX *pctx)
{
  nss_hash_final(pctx, digest, 16);
}