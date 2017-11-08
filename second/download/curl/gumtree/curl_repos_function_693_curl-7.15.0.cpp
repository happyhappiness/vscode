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
  (void)data;
  return NULL;
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
}