static CURLcode
ssl_connect_init_proxy(struct connectdata *conn, int sockindex)
{
  DEBUGASSERT(conn->bits.proxy_ssl_connected[sockindex]);
  if(ssl_connection_complete == conn->ssl[sockindex].state &&
     !conn->proxy_ssl[sockindex].use) {
    struct ssl_backend_data *pbdata;

    if(!Curl_ssl->support_https_proxy)
      return CURLE_NOT_BUILT_IN;

    /* The pointers to the ssl backend data, which is opaque here, are swapped
       rather than move the contents. */
    pbdata = conn->proxy_ssl[sockindex].backend;
    conn->proxy_ssl[sockindex] = conn->ssl[sockindex];

    memset(&conn->ssl[sockindex], 0, sizeof(conn->ssl[sockindex]));
    memset(pbdata, 0, Curl_ssl->sizeof_ssl_backend_data);

    conn->ssl[sockindex].backend = pbdata;
  }
  return CURLE_OK;
}