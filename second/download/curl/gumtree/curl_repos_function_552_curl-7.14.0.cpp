CURLcode Curl_ftp_connect(struct connectdata *conn,
                          bool *done) /* see description above */
{
  struct FTP *ftp;
  CURLcode result;

  *done = FALSE; /* default to not done yet */

  ftp = (struct FTP *)calloc(sizeof(struct FTP), 1);
  if(!ftp)
    return CURLE_OUT_OF_MEMORY;

  conn->proto.ftp = ftp;

  /* We always support persistant connections on ftp */
  conn->bits.close = FALSE;

  /* get some initial data into the ftp struct */
  ftp->bytecountp = &conn->bytecount;

  /* no need to duplicate them, this connectdata struct won't change */
  ftp->user = conn->user;
  ftp->passwd = conn->passwd;
  if (isBadFtpString(ftp->user) || isBadFtpString(ftp->passwd))
    return CURLE_URL_MALFORMAT;

  ftp->response_time = 3600; /* set default response time-out */

#ifndef CURL_DISABLE_HTTP
  if (conn->bits.tunnel_proxy) {
    /* BLOCKING */
    /* We want "seamless" FTP operations through HTTP proxy tunnel */
    result = Curl_ConnectHTTPProxyTunnel(conn, FIRSTSOCKET,
                                         conn->host.name, conn->remote_port);
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
  ftp->response = Curl_tvnow(); /* start response time-out now! */

  if(conn->data->state.used_interface == Curl_if_multi)
    result = Curl_ftp_multi_statemach(conn, done);
  else {
    result = ftp_easy_statemach(conn);
    if(!result)
      *done = TRUE;
  }

  return result;
}