int Curl_read(struct connectdata *conn, /* connection data */
              curl_socket_t sockfd,     /* read from this socket */
              char *buf,                /* store read data here */
              size_t buffersize,        /* max amount to read */
              ssize_t *n)               /* amount bytes read */
{
  ssize_t nread;

  /* Set 'num' to 0 or 1, depending on which socket that has been sent here.
     If it is the second socket, we set num to 1. Otherwise to 0. This lets
     us use the correct ssl handle. */
  int num = (sockfd == conn->sock[SECONDARYSOCKET]);

  *n=0; /* reset amount to zero */

  if(conn->ssl[num].use) {
    nread = Curl_ssl_recv(conn, num, buf, buffersize);

    if(nread == -1)
      return -1; /* -1 from Curl_ssl_recv() means EWOULDBLOCK */
  }
  else {
    *n=0; /* reset amount to zero */
    if(conn->sec_complete)
      nread = Curl_sec_read(conn, sockfd, buf, buffersize);
    else
      nread = sread(sockfd, buf, buffersize);

    if(-1 == nread) {
      int err = Curl_ourerrno();
#ifdef WIN32
      if(WSAEWOULDBLOCK == err)
#else
      if((EWOULDBLOCK == err) || (EAGAIN == err) || (EINTR == err))
#endif
        return -1;
    }
  }
  *n = nread;
  return CURLE_OK;
}