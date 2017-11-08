static CURLcode ftp_connect(struct connectdata *conn,
                                 bool *done) /* see description above */
{
  CURLcode result;
#ifndef CURL_DISABLE_HTTP
  /* for FTP over HTTP proxy */
  struct HTTP http_proxy;
  struct FTP *ftp_save;
#endif   /* CURL_DISABLE_HTTP */
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  struct SessionHandle *data=conn->data;

  *done = FALSE; /* default to not done yet */

  /* If there already is a protocol-specific struct allocated for this
     sessionhandle, deal with it */
  Curl_reset_reqproto(conn);

  result = ftp_init(conn);
  if(result)
    return result;

  /* We always support persistant connections on ftp */
  conn->bits.close = FALSE;

  ftpc->response_time = 3600000; /* set default response time-out */

#ifndef CURL_DISABLE_HTTP
  if(conn->bits.tunnel_proxy && conn->bits.httpproxy) {
    /* BLOCKING */
    /* We want "seamless" FTP operations through HTTP proxy tunnel */

    /* Curl_proxyCONNECT is based on a pointer to a struct HTTP at the member
     * conn->proto.http; we want FTP through HTTP and we have to change the
     * member temporarily for connecting to the HTTP proxy. After
     * Curl_proxyCONNECT we have to set back the member to the original struct
     * FTP pointer
     */
    ftp_save = data->state.proto.ftp;
    memset(&http_proxy, 0, sizeof(http_proxy));
    data->state.proto.http = &http_proxy;

    result = Curl_proxyCONNECT(conn, FIRSTSOCKET,
                               conn->host.name, conn->remote_port);

    data->state.proto.ftp = ftp_save;

    if(CURLE_OK != result)
      return result;
  }
#endif   /* CURL_DISABLE_HTTP */

  if(conn->protocol & PROT_FTPS) {
    /* BLOCKING */
    /* FTPS is simply ftp with SSL for the control channel */
    /* now, perform the SSL initialization for this socket */
    result = Curl_ssl_connect(conn, FIRSTSOCKET);
    if(result)
      return result;
  }

  /* When we connect, we start in the state where we await the 220
     response */
  ftp_respinit(conn); /* init the response reader stuff */
  state(conn, FTP_WAIT220);
  ftpc->response = Curl_tvnow(); /* start response time-out now! */

  if(data->state.used_interface == Curl_if_multi)
    result = ftp_multi_statemach(conn, done);
  else {
    result = ftp_easy_statemach(conn);
    if(!result)
      *done = TRUE;
  }

  return result;
}