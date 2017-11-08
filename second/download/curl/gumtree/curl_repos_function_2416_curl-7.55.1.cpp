size_t Curl_cyassl_version(char *buffer, size_t size)
{
#if LIBCYASSL_VERSION_HEX >= 0x03006000
  return snprintf(buffer, size, "wolfSSL/%s", wolfSSL_lib_version());
#elif defined(WOLFSSL_VERSION)
  return snprintf(buffer, size, "wolfSSL/%s", WOLFSSL_VERSION);
#elif defined(CYASSL_VERSION)
  return snprintf(buffer, size, "CyaSSL/%s", CYASSL_VERSION);
#else
  return snprintf(buffer, size, "CyaSSL/%s", "<1.8.8");
#endif
}