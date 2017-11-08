CURLcode Curl_ftp_multi_statemach(struct connectdata *conn,
                                  bool *done)
{
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  int rc;
  struct SessionHandle *data=conn->data;
  struct FTP *ftp = conn->proto.ftp;
  CURLcode result = CURLE_OK;
  long timeout_ms = ftp_state_timeout(conn);

  *done = FALSE; /* default to not done yet */

  if(timeout_ms <= 0) {
    failf(data, "FTP response timeout");
    return CURLE_OPERATION_TIMEDOUT;
  }

  rc = Curl_select(ftp->sendleft?CURL_SOCKET_BAD:sock, /* reading */
                   ftp->sendleft?sock:CURL_SOCKET_BAD, /* writing */
                   0);

  if(rc == -1) {
    failf(data, "select error");
    return CURLE_OUT_OF_MEMORY;
  }
  else if(rc != 0) {
    result = ftp_statemach_act(conn);
    *done = (ftp->state == FTP_STOP);
  }
  /* if rc == 0, then select() timed out */

  return result;
}