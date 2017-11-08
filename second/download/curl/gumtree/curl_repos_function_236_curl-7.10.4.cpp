static CURLcode ConnectPlease(struct connectdata *conn,
                              struct Curl_dns_entry *hostaddr,
                              bool *connected)
{
  CURLcode result;
  Curl_ipconnect *addr;

  /*************************************************************
   * Connect to server/proxy
   *************************************************************/
  result= Curl_connecthost(conn,
                           hostaddr,
                           conn->port,
                           &conn->firstsocket,
                           &addr,
                           connected);
  if(CURLE_OK == result) {
    /* All is cool, then we store the current information from the hostaddr
       struct to the serv_addr, as it might be needed later. The address
       returned from the function above is crucial here. */
    conn->connect_addr = hostaddr;

#ifdef ENABLE_IPV6
    conn->serv_addr = addr;
#else
    memset((char *) &conn->serv_addr, '\0', sizeof(conn->serv_addr));
    memcpy((char *)&(conn->serv_addr.sin_addr),
           (struct in_addr *)addr, sizeof(struct in_addr));
    conn->serv_addr.sin_family = hostaddr->addr->h_addrtype;
    conn->serv_addr.sin_port = htons((unsigned short)conn->port);
#endif

    if (conn->data->set.proxytype == CURLPROXY_SOCKS5) {
      return handleSock5Proxy(conn->data->state.proxyuser,
                              conn->data->state.proxypasswd,
                              conn,
                              conn->firstsocket) ?
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