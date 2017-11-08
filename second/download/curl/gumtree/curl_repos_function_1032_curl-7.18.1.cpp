int Curl_ssl_check_cxn(struct connectdata *conn)
{
#ifdef USE_SSLEAY
  return Curl_ossl_check_cxn(conn);
#else
#ifdef USE_NSS
  return Curl_nss_check_cxn(conn);
#else
#ifdef USE_QSOSSL
  return Curl_qsossl_check_cxn(conn);
#else
  (void)conn;
  /* TODO: we lack implementation of this for GnuTLS */
  return -1; /* connection status unknown */
#endif /* USE_QSOSSL */
#endif /* USE_NSS */
#endif /* USE_SSLEAY */
}