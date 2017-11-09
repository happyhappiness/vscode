static int MD5_Init(MD5_CTX *ctx)
{
  if(CryptAcquireContext(&ctx->hCryptProv, NULL, NULL,
                         PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
    CryptCreateHash(ctx->hCryptProv, CALG_MD5, 0, 0, &ctx->hHash);
  }
  return 1;
}