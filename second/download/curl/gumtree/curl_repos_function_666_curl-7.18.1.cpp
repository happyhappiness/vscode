CURLcode Curl_http_connect(struct connectdata *conn, bool *done)
{
  struct SessionHandle *data;
  CURLcode result;

  data=conn->data;

  /* We default to persistent connections. We set this already in this connect
     function to make the re-use checks properly be able to check this bit. */
  conn->bits.close = FALSE;

  /* If we are not using a proxy and we want a secure connection, perform SSL
   * initialization & connection now.  If using a proxy with https, then we
   * must tell the proxy to CONNECT to the host we want to talk to.  Only
   * after the connect has occurred, can we start talking SSL
   */

  if(conn->bits.tunnel_proxy && conn->bits.httpproxy) {

    /* either SSL over proxy, or explicitly asked for */
    result = Curl_proxyCONNECT(conn, FIRSTSOCKET,
                               conn->host.name,
                               conn->remote_port);
    if(CURLE_OK != result)
      return result;
  }

  if(conn->bits.tunnel_connecting) {
    /* nothing else to do except wait right now - we're not done here. */
    return CURLE_OK;
  }

  if(!data->state.this_is_a_follow) {
    /* this is not a followed location, get the original host name */
    if(data->state.first_host)
      /* Free to avoid leaking memory on multiple requests*/
      free(data->state.first_host);

    data->state.first_host = strdup(conn->host.name);
    if(!data->state.first_host)
      return CURLE_OUT_OF_MEMORY;
  }

  if(conn->protocol & PROT_HTTPS) {
    /* perform SSL initialization */
    if(data->state.used_interface == Curl_if_multi) {
      result = https_connecting(conn, done);
      if(result)
        return result;
    }
    else {
      /* BLOCKING */
      result = Curl_ssl_connect(conn, FIRSTSOCKET);
      if(result)
        return result;
      *done = TRUE;
    }
  }
  else {
    *done = TRUE;
  }

  return CURLE_OK;
}