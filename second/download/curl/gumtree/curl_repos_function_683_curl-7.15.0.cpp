int Curl_ssl_init(void)
{
  /* make sure this is only done once */
  if(init_ssl)
    return 1;
  init_ssl = TRUE; /* never again */

#ifdef USE_SSLEAY
  return Curl_ossl_init();
#else
#ifdef USE_GNUTLS
  return Curl_gtls_init();
#else
  /* no SSL support */
  return 1;
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
}