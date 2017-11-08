static CURLcode send_telnet_data(struct connectdata *conn,
                                 char *buffer, ssize_t nread)
{
  unsigned char outbuf[2];
  ssize_t bytes_written, total_written;
  int out_count;
  CURLcode rc = CURLE_OK;

  while(rc == CURLE_OK && nread--) {
    outbuf[0] = *buffer++;
    out_count = 1;
    if(outbuf[0] == CURL_IAC)
      outbuf[out_count++] = CURL_IAC;

    total_written = 0;
    do {
      /* Make sure socket is writable to avoid EWOULDBLOCK condition */
      struct pollfd pfd[1];
      pfd[0].fd = conn->sock[FIRSTSOCKET];
      pfd[0].events = POLLOUT;
      switch (Curl_poll(pfd, 1, -1)) {
        case -1:                    /* error, abort writing */
        case 0:                     /* timeout (will never happen) */
          rc = CURLE_SEND_ERROR;
          break;
        default:                    /* write! */
          bytes_written = 0;
          rc = Curl_write(conn, conn->sock[FIRSTSOCKET], outbuf+total_written,
                          out_count-total_written, &bytes_written);
          total_written += bytes_written;
          break;
      }
    /* handle partial write */
    } while(rc == CURLE_OK && total_written < out_count);
  }
  return rc;
}