static CURLcode
ssl_connect_init_proxy(struct connectdata *conn, int sockindex)
{
  DEBUGASSERT(conn->bits.proxy_ssl_connected[sockindex]);
  if(ssl_connection_complete == conn->ssl[sockindex].state &&
     !conn->proxy_ssl[sockindex].use) {
#if defined(HTTPS_PROXY_SUPPORT)
    conn->proxy_ssl[sockindex] = conn->ssl[sockindex];
    memset(&conn->ssl[sockindex], 0, sizeof(conn->ssl[sockindex]));
#else
    return CURLE_NOT_BUILT_IN;
#endif
  }
  return CURLE_OK;
}