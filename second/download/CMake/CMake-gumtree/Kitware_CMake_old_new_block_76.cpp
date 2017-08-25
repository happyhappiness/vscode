{
#ifdef WOLFSSL_VERSION
  return snprintf(buffer, size, "wolfSSL/%s", WOLFSSL_VERSION);
#elif defined(CYASSL_VERSION)
  return snprintf(buffer, size, "CyaSSL/%s", CYASSL_VERSION);
#else
  return snprintf(buffer, size, "CyaSSL/%s", "<1.8.8");
#endif
}