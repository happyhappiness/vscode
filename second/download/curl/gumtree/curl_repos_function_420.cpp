static CURLcode ConnectPlease(struct connectdata *conn,
                              struct Curl_dns_entry *hostaddr,
                              bool *connected)
{
  CURLcode result;
  Curl_addrinfo *addr;
  struct SessionHandle *data = conn->data;
  char *hostname = data->change.proxy?conn->proxy.name:conn->host.name;

  infof(data, "About to connect() to %s port %d\n",
        hostname, conn->port);

  /*************************************************************
   * Connect to server/proxy
   *************************************************************/
  result= Curl_connecthost(conn,
                           hostaddr,
                           &conn->sock[FIRSTSOCKET],
                           &addr,
                           connected);
  if(CURLE_OK == result) {
    /* All is cool, then we store the current information */
    conn->dns_entry = hostaddr;
    conn->ip_addr = addr;

    Curl_store_ip_addr(conn);

    if (conn->data->set.proxytype == CURLPROXY_SOCKS5) {
      return handleSock5Proxy(conn->proxyuser,
                              conn->proxypasswd,
                              conn) ?
        CURLE_COULDNT_CONNECT : CURLE_OK;
    }
    else if (conn->data->set.proxytype == CURLPROXY_HTTP) {
      /* do nothing here. handled later. */
    }
    else {
      failf(conn->data, "unknown proxytype option given");
      return CURLE_COULDNT_CONNECT;
    }
  }

  return result;
}