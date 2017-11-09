static CURLcode send_telnet_data(struct connectdata *conn,
                                 char *buffer, ssize_t nread)
{
  ssize_t escapes, i, j, outlen;
  unsigned char *outbuf = NULL;
  CURLcode result = CURLE_OK;
  ssize_t bytes_written, total_written;

  /* Determine size of new buffer after escaping */
  escapes = 0;
  for(i = 0; i < nread; i++)
    if((unsigned char)buffer[i] == CURL_IAC)
      escapes++;
  outlen = nread + escapes;

  if(outlen == nread)
    outbuf = (unsigned char *)buffer;
  else {
    outbuf = malloc(nread + escapes + 1);
    if(!outbuf)
      return CURLE_OUT_OF_MEMORY;

    j = 0;
    for(i = 0; i < nread; i++) {
      outbuf[j++] = buffer[i];
      if((unsigned char)buffer[i] == CURL_IAC)
        outbuf[j++] = CURL_IAC;
    }
    outbuf[j] = '\0';
  }

  total_written = 0;
  while(!result && total_written < outlen) {
    /* Make sure socket is writable to avoid EWOULDBLOCK condition */
    struct pollfd pfd[1];
    pfd[0].fd = conn->sock[FIRSTSOCKET];
    pfd[0].events = POLLOUT;
    switch(Curl_poll(pfd, 1, -1)) {
      case -1:                    /* error, abort writing */
      case 0:                     /* timeout (will never happen) */
        result = CURLE_SEND_ERROR;
        break;
      default:                    /* write! */
        bytes_written = 0;
        result = Curl_write(conn, conn->sock[FIRSTSOCKET],
                            outbuf + total_written,
                            outlen - total_written,
                            &bytes_written);
        total_written += bytes_written;
        break;
    }
  }

  /* Free malloc copy if escaped */
  if(outbuf != (unsigned char *)buffer)
    free(outbuf);

  return result;
}