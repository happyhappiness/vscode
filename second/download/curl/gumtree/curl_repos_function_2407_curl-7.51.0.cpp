bool Curl_ssl_false_start(void)
{
#ifdef curlssl_false_start
  return curlssl_false_start();
#else
  return FALSE;
#endif
}