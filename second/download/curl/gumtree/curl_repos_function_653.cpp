CURLcode Curl_ssl_set_engine(struct SessionHandle *data, const char *engine)
{
#ifdef USE_SSLEAY
  return Curl_ossl_set_engine(data, engine);
#else
#ifdef USE_GNUTLS
  /* FIX: add code here */
  (void)data;
  (void)engine;
  return CURLE_FAILED_INIT;
#else
  /* no SSL layer */
  (void)data;
  (void)engine;
  return CURLE_FAILED_INIT;
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
}