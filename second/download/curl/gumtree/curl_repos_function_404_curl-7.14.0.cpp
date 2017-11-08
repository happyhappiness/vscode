CURLcode Curl_http_connect(struct connectdata *conn, bool *done)
{
  struct SessionHandle *data;
  CURLcode result;

  data=conn->data;

  /* If we are not using a proxy and we want a secure connection, perform SSL
   * initialization & connection now.  If using a proxy with https, then we
   * must tell the proxy to CONNECT to the host we want to talk to.  Only
   * after the connect has occured, can we start talking SSL
   */

  if(conn->bits.tunnel_proxy) {

    /* either SSL over proxy, or explicitly asked for */
    result = Curl_ConnectHTTPProxyTunnel(conn, FIRSTSOCKET,
                                         conn->host.name,
                                         conn->remote_port);
    if(CURLE_OK != result)
      return result;
  }

  if(conn->protocol & PROT_HTTPS) {
    /* perform SSL initialization for this socket */
    result = Curl_ssl_connect(conn, FIRSTSOCKET);
    if(result)
      return result;
  }

  if(!data->state.this_is_a_follow) {
    /* this is not a followed location, get the original host name */
    if (data->state.first_host)
      /* Free to avoid leaking memory on multiple requests*/
      free(data->state.first_host);

    data->state.first_host = strdup(conn->host.name);
  }

  *done = TRUE;

  return CURLE_OK;
}