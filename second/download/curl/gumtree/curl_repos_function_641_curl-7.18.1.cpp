static int blockread_all(struct connectdata *conn, /* connection data */
                         curl_socket_t sockfd,     /* read from this socket */
                         char *buf,                /* store read data here */
                         ssize_t buffersize,       /* max amount to read */
                         ssize_t *n,               /* amount bytes read */
                         long conn_timeout)        /* timeout for data wait
                                                      relative to
                                                      conn->created */
{
  ssize_t nread;
  ssize_t allread = 0;
  int result;
  struct timeval tvnow;
  long conntime;
  *n = 0;
  do {
    tvnow = Curl_tvnow();
    /* calculating how long connection is establishing */
    conntime = Curl_tvdiff(tvnow, conn->created);
    if(conntime > conn_timeout) {
      /* we already got the timeout */
      result = ~CURLE_OK;
      break;
    }
    if(Curl_socket_ready(sockfd, CURL_SOCKET_BAD,
                   (int)(conn_timeout - conntime)) <= 0) {
      result = ~CURLE_OK;
      break;
    }
    result = Curl_read(conn, sockfd, buf, buffersize, &nread);
    if(result)
      break;

    if(buffersize == nread) {
      allread += nread;
      *n = allread;
      result = CURLE_OK;
      break;
    }
    if(!nread) {
      result = ~CURLE_OK;
      break;
    }

    buffersize -= nread;
    buf += nread;
    allread += nread;
  } while(1);
  return result;
}