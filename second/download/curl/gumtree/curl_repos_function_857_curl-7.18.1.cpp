static CURLcode AllowServerConnect(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  curl_socket_t sock = conn->sock[SECONDARYSOCKET];
  long timeout_ms = Curl_timeleft(conn, NULL, TRUE);

  if(timeout_ms < 0) {
    /* if a timeout was already reached, bail out */
    failf(data, "Timed out before server could connect to us");
    return CURLE_OPERATION_TIMEDOUT;
  }

  switch (Curl_socket_ready(sock, CURL_SOCKET_BAD, (int)timeout_ms)) {
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
      curl_socket_t s = CURL_SOCKET_BAD;
#ifdef ENABLE_IPV6
      struct Curl_sockaddr_storage add;
#else
      struct sockaddr_in add;
#endif
      socklen_t size = (socklen_t) sizeof(add);

      if(0 == getsockname(sock, (struct sockaddr *) &add, &size)) {
        size = sizeof(add);

        s=accept(sock, (struct sockaddr *) &add, &size);
      }
      sclose(sock); /* close the first socket */

      if(CURL_SOCKET_BAD == s) {
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