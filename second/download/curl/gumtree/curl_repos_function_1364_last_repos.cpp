int Curl_blockread_all(struct connectdata *conn, /* connection data */
                       curl_socket_t sockfd,     /* read from this socket */
                       char *buf,                /* store read data here */
                       ssize_t buffersize,       /* max amount to read */
                       ssize_t *n)               /* amount bytes read */
{
  ssize_t nread;
  ssize_t allread = 0;
  int result;
  time_t timeleft;
  *n = 0;
  for(;;) {
    timeleft = Curl_timeleft(conn->data, NULL, TRUE);
    if(timeleft < 0) {
      /* we already got the timeout */
      result = CURLE_OPERATION_TIMEDOUT;
      break;
    }
    if(SOCKET_READABLE(sockfd, timeleft) <= 0) {
      result = ~CURLE_OK;
      break;
    }
    result = Curl_read_plain(sockfd, buf, buffersize, &nread);
    if(CURLE_AGAIN == result)
      continue;
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
  }
  return result;
}