struct curl_slist *Curl_ssl_engines_list(struct SessionHandle *data)
{
#ifdef USE_SSLEAY
  return Curl_ossl_engines_list(data);
#else
#ifdef USE_GNUTLS
  /* FIX: add code here? */
  (void)data;
  return NULL;
#else
#ifdef USE_NSS
  /* In theory we could return the PKCS#11 modules loaded but that
   * would just confuse things */
  (void)data;
  return NULL;
#else
#ifdef USE_QSOSSL
  /* No engine support in QSOSSL. */
  (void)data;
  return NULL;
#else
  (void)data;
  return NULL;
#endif /* USE_QSOSSL */
#endif /* USE_NSS */
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
}