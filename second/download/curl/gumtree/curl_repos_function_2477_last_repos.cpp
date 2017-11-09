static CURLcode Curl_schannel_random(struct Curl_easy *data UNUSED_PARAM,
                                     unsigned char *entropy, size_t length)
{
  HCRYPTPROV hCryptProv = 0;

  (void)data;

  if(!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL,
                          CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
    return CURLE_FAILED_INIT;

  if(!CryptGenRandom(hCryptProv, (DWORD)length, entropy)) {
    CryptReleaseContext(hCryptProv, 0UL);
    return CURLE_FAILED_INIT;
  }

  CryptReleaseContext(hCryptProv, 0UL);
  return CURLE_OK;
}