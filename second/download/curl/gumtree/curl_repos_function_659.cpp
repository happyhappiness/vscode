size_t Curl_ssl_version(char *buffer, size_t size)
{
#ifdef USE_SSLEAY
  return Curl_ossl_version(buffer, size);
#else
#ifdef USE_GNUTLS
  return Curl_gtls_version(buffer, size);
#else
  (void)buffer;
  (void)size;
  return 0; /* no SSL support */
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
}