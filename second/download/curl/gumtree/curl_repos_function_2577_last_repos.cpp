size_t Curl_ssl_version(char *buffer, size_t size)
{
#ifdef CURL_WITH_MULTI_SSL
  return Curl_multissl_version(buffer, size);
#else
  return Curl_ssl->version(buffer, size);
#endif
}