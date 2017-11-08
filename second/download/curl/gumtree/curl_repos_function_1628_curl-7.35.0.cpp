static CURLcode AllowServerConnect(struct connectdata *conn, bool *connected)
{
  struct SessionHandle *data = conn->data;
  long timeout_ms;
  CURLcode ret = CURLE_OK;

  *connected = FALSE;
  infof(data, "Preparing for accepting server on data port\n");

  /* Save the time we start accepting server connect */
  Curl_pgrsTime(data, TIMER_STARTACCEPT);

  timeout_ms = ftp_timeleft_accept(data);
  if(timeout_ms < 0) {
    /* if a timeout was already reached, bail out */
    failf(data, "Accept timeout occurred while waiting server connect");
    return CURLE_FTP_ACCEPT_TIMEOUT;
  }

  /* see if the connection request is already here */
  ret = ReceivedServerConnect(conn, connected);
  if(ret)
    return ret;

  if(*connected) {
    ret = AcceptServerConnect(conn);
    if(ret)
      return ret;

    ret = InitiateTransfer(conn);
    if(ret)
      return ret;
  }
  else {
    /* Add timeout to multi handle and break out of the loop */
    if(ret == CURLE_OK && *connected == FALSE) {
      if(data->set.accepttimeout > 0)
        Curl_expire(data, data->set.accepttimeout);
      else
        Curl_expire(data, DEFAULT_ACCEPT_TIMEOUT);
    }
  }

  return ret;
}