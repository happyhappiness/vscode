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
#ifdef USE_NSS
  /* A no-op for NSS */
  (void)data;
  return CURLE_FAILED_INIT;
#else
#ifdef USE_QSOSSL
  /* A no-op for QSOSSL */
  (void)data;
  return CURLE_FAILED_INIT;
#else
  /* No SSL layer */
  (void)data;
  return CURLE_FAILED_INIT;
#endif /* USE_QSOSSL */
#endif /* USE_NSS */
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
}