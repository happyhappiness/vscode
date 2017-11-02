static CURLcode proxy_magic(struct connectdata *conn,
                            char *newhost, unsigned short newport,
                            bool *magicdone)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

#if defined(CURL_DISABLE_PROXY)
  (void) newhost;
  (void) newport;
#endif

  *magicdone = FALSE;

  switch(conn->proxytype) {
  case CURLPROXY_SOCKS5:
  case CURLPROXY_SOCKS5_HOSTNAME:
    result = Curl_SOCKS5(conn->proxyuser, conn->proxypasswd, newhost,
                         newport, SECONDARYSOCKET, conn);
    *magicdone = TRUE;
    break;
  case CURLPROXY_SOCKS4:
    result = Curl_SOCKS4(conn->proxyuser, newhost, newport,
                         SECONDARYSOCKET, conn, FALSE);
    *magicdone = TRUE;
    break;
  case CURLPROXY_SOCKS4A:
    result = Curl_SOCKS4(conn->proxyuser, newhost, newport,
                         SECONDARYSOCKET, conn, TRUE);
    *magicdone = TRUE;
    break;
  case CURLPROXY_HTTP:
  case CURLPROXY_HTTP_1_0:
    /* do nothing here. handled later. */
    break;
  default:
    failf(data, "unknown proxytype option given");
    result = CURLE_COULDNT_CONNECT;
    break;
  }

  if(conn->bits.tunnel_proxy && conn->bits.httpproxy) {
    /* BLOCKING */
    /* We want "seamless" FTP operations through HTTP proxy tunnel */

    /* Curl_proxyCONNECT is based on a pointer to a struct HTTP at the
     * member conn->proto.http; we want FTP through HTTP and we have to
     * change the member temporarily for connecting to the HTTP proxy. After
     * Curl_proxyCONNECT we have to set back the member to the original
     * struct FTP pointer
     */
    struct HTTP http_proxy;
    struct FTP *ftp_save = data->req.protop;
    memset(&http_proxy, 0, sizeof(http_proxy));
    data->req.protop = &http_proxy;

    result = Curl_proxyCONNECT(conn, SECONDARYSOCKET, newhost, newport);

    data->req.protop = ftp_save;

    if(result)
      return result;

    if(conn->tunnel_state[SECONDARYSOCKET] != TUNNEL_COMPLETE) {
      /* the CONNECT procedure is not complete, the tunnel is not yet up */
      state(conn, FTP_STOP); /* this phase is completed */
      return result;
    }
    else
      *magicdone = TRUE;
  }

  return result;
}