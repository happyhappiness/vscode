int Curl_schannel_random(unsigned char *entropy, size_t length)
{
  HCRYPTPROV hCryptProv = 0;

  if(!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL,
                          CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
    return 1;

  if(!CryptGenRandom(hCryptProv, (DWORD)length, entropy)) {
    CryptReleaseContext(hCryptProv, 0UL);
    return 1;
  }

  CryptReleaseContext(hCryptProv, 0UL);
  return 0;
}