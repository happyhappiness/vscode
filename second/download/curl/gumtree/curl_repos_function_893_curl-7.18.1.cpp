static CURLcode ftp_easy_statemach(struct connectdata *conn)
{
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  int rc;
  struct SessionHandle *data=conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  CURLcode result = CURLE_OK;

  while(ftpc->state != FTP_STOP) {
    long timeout_ms = ftp_state_timeout(conn);

    if(timeout_ms <=0 ) {
      failf(data, "FTP response timeout");
      return CURLE_OPERATION_TIMEDOUT; /* already too little time */
    }

    rc = Curl_socket_ready(ftpc->sendleft?CURL_SOCKET_BAD:sock, /* reading */
                           ftpc->sendleft?sock:CURL_SOCKET_BAD, /* writing */
                           (int)timeout_ms);

    if(rc == -1) {
      failf(data, "select/poll error");
      return CURLE_OUT_OF_MEMORY;
    }
    else if(rc == 0) {
      result = CURLE_OPERATION_TIMEDOUT;
      break;
    }
    else {
      result = ftp_statemach_act(conn);
      if(result)
        break;
    }
  }

  return result;
}