static void win32_crypto_final(struct win32_crypto_hash *ctx,
                               unsigned char *digest,
                               unsigned int digestLen)
{
  unsigned long length;
  CryptGetHashParam(ctx->hHash, HP_HASHVAL, NULL, &length, 0);
  if(length == digestLen)
    CryptGetHashParam(ctx->hHash, HP_HASHVAL, digest, &length, 0);
  if(ctx->hHash)
    CryptDestroyHash(ctx->hHash);
  if(ctx->hCryptProv)
    CryptReleaseContext(ctx->hCryptProv, 0);
}