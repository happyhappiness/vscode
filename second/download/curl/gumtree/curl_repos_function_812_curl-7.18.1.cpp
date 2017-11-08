int Curl_read(struct connectdata *conn, /* connection data */
              curl_socket_t sockfd,     /* read from this socket */
              char *buf,                /* store read data here */
              size_t sizerequested,     /* max amount to read */
              ssize_t *n)               /* amount bytes read */
{
  ssize_t nread = 0;
  size_t bytesfromsocket = 0;
  char *buffertofill = NULL;
  bool pipelining = (bool)(conn->data->multi &&
                     Curl_multi_canPipeline(conn->data->multi));

  /* Set 'num' to 0 or 1, depending on which socket that has been sent here.
     If it is the second socket, we set num to 1. Otherwise to 0. This lets
     us use the correct ssl handle. */
  int num = (sockfd == conn->sock[SECONDARYSOCKET]);

  *n=0; /* reset amount to zero */

  /* If session can pipeline, check connection buffer  */
  if(pipelining) {
    size_t bytestocopy = MIN(conn->buf_len - conn->read_pos, sizerequested);

    /* Copy from our master buffer first if we have some unread data there*/
    if(bytestocopy > 0) {
      memcpy(buf, conn->master_buffer + conn->read_pos, bytestocopy);
      conn->read_pos += bytestocopy;
      conn->bits.stream_was_rewound = FALSE;

      *n = (ssize_t)bytestocopy;
      return CURLE_OK;
    }
    /* If we come here, it means that there is no data to read from the buffer,
     * so we read from the socket */
    bytesfromsocket = MIN(sizerequested, BUFSIZE * sizeof (char));
    buffertofill = conn->master_buffer;
  }
  else {
    bytesfromsocket = MIN((long)sizerequested, conn->data->set.buffer_size ?
                          conn->data->set.buffer_size : BUFSIZE);
    buffertofill = buf;
  }

  if(conn->ssl[num].state == ssl_connection_complete) {
    nread = Curl_ssl_recv(conn, num, buffertofill, bytesfromsocket);

    if(nread == -1) {
      return -1; /* -1 from Curl_ssl_recv() means EWOULDBLOCK */
    }
  }
#ifdef USE_LIBSSH2
  else if(conn->protocol & (PROT_SCP|PROT_SFTP)) {
    if(conn->protocol & PROT_SCP)
      nread = Curl_scp_recv(conn, num, buffertofill, bytesfromsocket);
    else if(conn->protocol & PROT_SFTP)
      nread = Curl_sftp_recv(conn, num, buffertofill, bytesfromsocket);
#ifdef LIBSSH2CHANNEL_EAGAIN
    if((nread == LIBSSH2CHANNEL_EAGAIN) || (nread == 0))
      /* EWOULDBLOCK */
      return -1;
#endif
    if(nread < 0)
      /* since it is negative and not EGAIN, it was a protocol-layer error */
      return CURLE_RECV_ERROR;
  }
#endif /* !USE_LIBSSH2 */
  else {
    if(conn->sec_complete)
      nread = Curl_sec_read(conn, sockfd, buffertofill,
                            bytesfromsocket);
    else
      nread = sread(sockfd, buffertofill, bytesfromsocket);

    if(-1 == nread) {
      int err = SOCKERRNO;
#ifdef USE_WINSOCK
      if(WSAEWOULDBLOCK == err)
#else
      if((EWOULDBLOCK == err) || (EAGAIN == err) || (EINTR == err))
#endif
        return -1;
    }
  }

  if(nread >= 0) {
    if(pipelining) {
      memcpy(buf, conn->master_buffer, nread);
      conn->buf_len = nread;
      conn->read_pos = nread;
    }

    *n += nread;
  }

  return CURLE_OK;
}