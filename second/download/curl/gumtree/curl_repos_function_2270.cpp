bool Curl_ssl_cert_status_request(void)
{
#ifdef curlssl_cert_status_request
  return curlssl_cert_status_request();
#else
  return FALSE;
#endif
}