bool Curl_ssl_data_pending(const struct connectdata *conn,
                           int connindex)
{
#ifdef USE_SSLEAY
  /* OpenSSL-specific */
  if(conn->ssl[connindex].handle)
    /* SSL is in use */
    return (bool)(0 != SSL_pending(conn->ssl[connindex].handle));
#else
  (void)conn;
  (void)connindex;
#endif
  return FALSE; /* nothing pending */

}