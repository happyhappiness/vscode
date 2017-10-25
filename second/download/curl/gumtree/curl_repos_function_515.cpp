static CURLcode AllowServerConnect(struct connectdata *conn)
{
  int timeout_ms;
  struct SessionHandle *data = conn->data;
  curl_socket_t sock = conn->sock[SECONDARYSOCKET];
  struct timeval now = Curl_tvnow();
  long timespent = Curl_tvdiff(Curl_tvnow(), now)/1000;
  long timeout = data->set.connecttimeout?data->set.connecttimeout:
    (data->set.timeout?data->set.timeout: 0);

  if(timeout) {
    timeout -= timespent;
    if(timeout<=0) {
      failf(data, "Timed out before server could connect to us");
      return CURLE_OPERATION_TIMEDOUT;
    }
  }

  /* We allow the server 60 seconds to connect to us, or a custom timeout.
     Note the typecast here. */
  timeout_ms = (timeout?(int)timeout:60) * 1000;

  switch (Curl_select(sock, CURL_SOCKET_BAD, timeout_ms)) {
  case -1: /* error */
    /* let's die here */
    failf(data, "Error while waiting for server connect");
    return CURLE_FTP_PORT_FAILED;
  case 0:  /* timeout */
    /* let's die here */
    failf(data, "Timeout while waiting for server connect");
    return CURLE_FTP_PORT_FAILED;
  default:
    /* we have received data here */
    {
      curl_socket_t s;
      size_t size = sizeof(struct sockaddr_in);
      struct sockaddr_in add;

      getsockname(sock, (struct sockaddr *) &add, (socklen_t *)&size);
      s=accept(sock, (struct sockaddr *) &add, (socklen_t *)&size);

      sclose(sock); /* close the first socket */

      if (CURL_SOCKET_BAD == s) {
        /* DIE! */
        failf(data, "Error accept()ing server connect");
        return CURLE_FTP_PORT_FAILED;
      }
      infof(data, "Connection accepted from server\n");

      conn->sock[SECONDARYSOCKET] = s;
      Curl_nonblock(s, TRUE); /* enable non-blocking */
    }
    break;
  }

  return CURLE_OK;
}