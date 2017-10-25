static CURLcode ftp_easy_statemach(struct connectdata *conn)
{
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  int rc;
  struct SessionHandle *data=conn->data;
  struct FTP *ftp = conn->proto.ftp;
  CURLcode result = CURLE_OK;

  while(ftp->state != FTP_STOP) {
    long timeout_ms = ftp_state_timeout(conn);

    if(timeout_ms <=0 ) {
      failf(data, "FTP response timeout");
      return CURLE_OPERATION_TIMEDOUT; /* already too little time */
    }

    rc = Curl_select(ftp->sendleft?CURL_SOCKET_BAD:sock, /* reading */
                     ftp->sendleft?sock:CURL_SOCKET_BAD, /* writing */
                     (int)timeout_ms);

    if(rc == -1) {
      failf(data, "select error");
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