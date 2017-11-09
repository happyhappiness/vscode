static void nss_hash_final(void **pctx, unsigned char *out, unsigned int len)
{
  PK11Context *ctx = *pctx;
  unsigned int outlen;
  PK11_DigestFinal(ctx, out, &outlen, len);
  PK11_DestroyContext(ctx, PR_TRUE);
}