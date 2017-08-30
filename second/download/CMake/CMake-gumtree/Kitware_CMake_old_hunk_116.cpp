
size_t Curl_cyassl_version(char *buffer, size_t size)
{
#ifdef WOLFSSL_VERSION
  return snprintf(buffer, size, "wolfSSL/%s", WOLFSSL_VERSION);
#elif defined(CYASSL_VERSION)
  return snprintf(buffer, size, "CyaSSL/%s", CYASSL_VERSION);
