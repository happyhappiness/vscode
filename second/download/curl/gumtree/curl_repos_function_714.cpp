static int SHA1_Init(SHA_CTX *ctx)
{
  if(CryptAcquireContext(&ctx->hCryptProv, NULL, NULL,
                         PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
    CryptCreateHash(ctx->hCryptProv, CALG_SHA1, 0, 0, &ctx->hHash);
  }
  return 1;
}