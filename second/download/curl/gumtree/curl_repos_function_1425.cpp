CURLcode Curl_proxy_connect(struct connectdata *conn)
{
  if(conn->bits.tunnel_proxy && conn->bits.httpproxy) {
#ifndef CURL_DISABLE_PROXY
    /* for [protocol] tunneled through HTTP proxy */
    struct HTTP http_proxy;
    void *prot_save;
    CURLcode result;

    /* BLOCKING */
    /* We want "seamless" operations through HTTP proxy tunnel */

    /* Curl_proxyCONNECT is based on a pointer to a struct HTTP at the
     * member conn->proto.http; we want [protocol] through HTTP and we have
     * to change the member temporarily for connecting to the HTTP
     * proxy. After Curl_proxyCONNECT we have to set back the member to the
     * original pointer
     *
     * This function might be called several times in the multi interface case
     * if the proxy's CONNTECT response is not instant.
     */
    prot_save = conn->data->req.protop;
    memset(&http_proxy, 0, sizeof(http_proxy));
    conn->data->req.protop = &http_proxy;
    connkeep(conn, "HTTP proxy CONNECT");
    result = Curl_proxyCONNECT(conn, FIRSTSOCKET,
                               conn->host.name, conn->remote_port);
    conn->data->req.protop = prot_save;
    if(CURLE_OK != result)
      return result;
#else
    return CURLE_NOT_BUILT_IN;
#endif
  }
  /* no HTTP tunnel proxy, just return */
  return CURLE_OK;
}