static int SHA256_Init(SHA256_CTX *ctx)
{
  if(CryptAcquireContext(&ctx->hCryptProv, NULL, NULL,
                         PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
    CryptCreateHash(ctx->hCryptProv, CALG_SHA_256, 0, 0, &ctx->hHash);
  }
  return 1;
}