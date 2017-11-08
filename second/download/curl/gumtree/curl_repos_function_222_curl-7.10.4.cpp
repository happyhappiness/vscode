CURLcode Curl_http_connect(struct connectdata *conn)
{
  struct SessionHandle *data;
  CURLcode result;

  data=conn->data;

  /* If we are not using a proxy and we want a secure connection,
   * perform SSL initialization & connection now.
   * If using a proxy with https, then we must tell the proxy to CONNECT
   * us to the host we want to talk to.  Only after the connect
   * has occured, can we start talking SSL
   */

  if(conn->bits.httpproxy &&
     ((conn->protocol & PROT_HTTPS) || data->set.tunnel_thru_httpproxy)) {

    /* either HTTPS over proxy, OR explicitly asked for a tunnel */
    result = Curl_ConnectHTTPProxyTunnel(conn, conn->firstsocket,
                                         conn->hostname, conn->remote_port);
    if(CURLE_OK != result)
      return result;
  }    

  if(conn->protocol & PROT_HTTPS) {
    /* now, perform the SSL initialization for this socket */
    result = Curl_SSLConnect(conn);
    if(result)
      return result;
  }

  if(conn->bits.user_passwd && !data->state.this_is_a_follow) {
    /* Authorization: is requested, this is not a followed location, get the
       original host name */
    if (data->state.auth_host)
      /* Free to avoid leaking memory on multiple requests*/
      free(data->state.auth_host);

    data->state.auth_host = strdup(conn->hostname);
  }

  return CURLE_OK;
}