static CURLcode ssh_block_statemach(struct connectdata *conn,
                                   bool duringconnect)
{
  struct ssh_conn *sshc = &conn->proto.sshc;
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  while((sshc->state != SSH_STOP) && !result) {
    bool block;
    long left;

    result = ssh_statemach_act(conn, &block);
    if(result)
      break;

    if(Curl_pgrsUpdate(conn))
      return CURLE_ABORTED_BY_CALLBACK;
    else {
      struct timeval now = Curl_tvnow();
      result = Curl_speedcheck(data, now);
      if(result)
        break;
    }

    left = Curl_timeleft(data, NULL, duringconnect);
    if(left < 0) {
      failf(data, "Operation timed out");
      return CURLE_OPERATION_TIMEDOUT;
    }

#ifdef HAVE_LIBSSH2_SESSION_BLOCK_DIRECTION
    if(!result && block) {
      int dir = libssh2_session_block_directions(sshc->ssh_session);
      curl_socket_t sock = conn->sock[FIRSTSOCKET];
      curl_socket_t fd_read = CURL_SOCKET_BAD;
      curl_socket_t fd_write = CURL_SOCKET_BAD;
      if(LIBSSH2_SESSION_BLOCK_INBOUND & dir)
        fd_read = sock;
      if(LIBSSH2_SESSION_BLOCK_OUTBOUND & dir)
        fd_write = sock;
      /* wait for the socket to become ready */
      Curl_socket_ready(fd_read, fd_write,
                        left>1000?1000:left); /* ignore result */
    }
#endif

  }

  return result;
}