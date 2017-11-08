static void SHA1_Final(unsigned char digest[20], SHA_CTX *pctx)
{
  nss_hash_final(pctx, digest, 20);
}