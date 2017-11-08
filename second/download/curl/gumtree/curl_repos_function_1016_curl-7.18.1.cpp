void Curl_ssl_cleanup(void)
{
  if(init_ssl) {
    /* only cleanup if we did a previous init */
#ifdef USE_SSLEAY
    Curl_ossl_cleanup();
#else
#ifdef USE_GNUTLS
    Curl_gtls_cleanup();
#else
#ifdef USE_NSS
    Curl_nss_cleanup();
#else
#ifdef USE_QSOSSL
    Curl_qsossl_cleanup();
#endif /* USE_QSOSSL */
#endif /* USE_NSS */
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
    init_ssl = FALSE;
  }
}