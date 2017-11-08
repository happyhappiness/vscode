size_t Curl_cyassl_version(char *buffer, size_t size)
{
#ifdef CYASSL_VERSION
  return snprintf(buffer, size, "CyaSSL/%s", CYASSL_VERSION);
#else
  return snprintf(buffer, size, "CyaSSL/%s", "<1.8.8");
#endif
}