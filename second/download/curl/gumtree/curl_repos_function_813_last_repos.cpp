static void SHA256_Final(unsigned char digest[32], SHA256_CTX *pctx)
{
  nss_hash_final(pctx, digest, 32);
}