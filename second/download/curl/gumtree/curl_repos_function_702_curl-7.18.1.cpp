static CURLcode ConnectPlease(struct SessionHandle *data,
                              struct connectdata *conn,
                              struct Curl_dns_entry *hostaddr,
                              bool *connected)
{
  CURLcode result;
  Curl_addrinfo *addr;
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  char *hostname = conn->bits.proxy?conn->proxy.name:conn->host.name;

  infof(data, "About to connect() to %s%s port %d (#%d)\n",
        conn->bits.proxy?"proxy ":"",
        hostname, conn->port, conn->connectindex);
#endif

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

    result = Curl_store_ip_addr(conn);

    if(CURLE_OK == result) {

      switch(data->set.proxytype) {
      case CURLPROXY_SOCKS5:
      case CURLPROXY_SOCKS5_HOSTNAME:
        result = Curl_SOCKS5(conn->proxyuser, conn->proxypasswd,
                             conn->host.name, conn->remote_port,
                             FIRSTSOCKET, conn);
        break;
      case CURLPROXY_HTTP:
        /* do nothing here. handled later. */
        break;
      case CURLPROXY_SOCKS4:
        result = Curl_SOCKS4(conn->proxyuser, conn->host.name,
                             conn->remote_port, FIRSTSOCKET, conn, FALSE);
        break;
      case CURLPROXY_SOCKS4A:
        result = Curl_SOCKS4(conn->proxyuser, conn->host.name,
                             conn->remote_port, FIRSTSOCKET, conn, TRUE);
        break;
      default:
        failf(data, "unknown proxytype option given");
        result = CURLE_COULDNT_CONNECT;
        break;
      }
    }
  }
  if(result)
    *connected = FALSE; /* mark it as not connected */

  return result;
}