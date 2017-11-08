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
#ifdef USE_NSS
  return Curl_nss_init();
#else
#ifdef USE_QSOSSL
  return Curl_qsossl_init();
#else
  /* no SSL support */
  return 1;
#endif /* USE_QSOSSL */
#endif /* USE_NSS */
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
}