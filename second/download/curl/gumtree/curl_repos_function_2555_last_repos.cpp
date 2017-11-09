int Curl_ssl_backend(void)
{
#ifdef USE_SSL
  multissl_init(NULL);
  return Curl_ssl->info.id;
#else
  return (int)CURLSSLBACKEND_NONE;
#endif
}