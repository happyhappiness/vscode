static CURLcode https_proxy_connect(struct connectdata *conn, int sockindex)
{
#ifdef USE_SSL
  CURLcode result = CURLE_OK;
  DEBUGASSERT(conn->http_proxy.proxytype == CURLPROXY_HTTPS);
  if(!conn->bits.proxy_ssl_connected[sockindex]) {
    /* perform SSL initialization for this socket */
    result =
      Curl_ssl_connect_nonblocking(conn, sockindex,
                                   &conn->bits.proxy_ssl_connected[sockindex]);
    if(result)
      conn->bits.close = TRUE; /* a failed connection is marked for closure to
                                  prevent (bad) re-use or similar */
  }
  return result;
#else
  (void) conn;
  (void) sockindex;
  return CURLE_NOT_BUILT_IN;
#endif
}