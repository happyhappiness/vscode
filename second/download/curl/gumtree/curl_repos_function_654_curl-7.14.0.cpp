CURLcode Curl_ssl_set_engine_default(struct SessionHandle *data)
{
#ifdef USE_SSLEAY
  return Curl_ossl_set_engine_default(data);
#else
#ifdef USE_GNUTLS
  /* FIX: add code here */
  (void)data;
  return CURLE_FAILED_INIT;
#else
  /* No SSL layer */
  (void)data;
  return CURLE_FAILED_INIT;
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
}