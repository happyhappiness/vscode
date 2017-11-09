static CURLcode AllowServerConnect(struct connectdata *conn, bool *connected)
{
  struct Curl_easy *data = conn->data;
  time_t timeout_ms;
  CURLcode result = CURLE_OK;

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
  result = ReceivedServerConnect(conn, connected);
  if(result)
    return result;

  if(*connected) {
    result = AcceptServerConnect(conn);
    if(result)
      return result;

    result = InitiateTransfer(conn);
    if(result)
      return result;
  }
  else {
    /* Add timeout to multi handle and break out of the loop */
    if(!result && *connected == FALSE) {
      Curl_expire(data, data->set.accepttimeout > 0 ?
                  data->set.accepttimeout: DEFAULT_ACCEPT_TIMEOUT, 0);
    }
  }

  return result;
}