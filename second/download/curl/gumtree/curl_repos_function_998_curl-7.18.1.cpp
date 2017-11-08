ssize_t Curl_nss_recv(struct connectdata * conn, /* connection data */
                      int num,                   /* socketindex */
                      char *buf,                 /* store read data here */
                      size_t buffersize,         /* max amount to read */
                      bool * wouldblock)
{
  ssize_t nread;
  struct SessionHandle *data = conn->data;
  PRInt32 timeout;

  if(data->set.timeout)
    timeout = PR_SecondsToInterval(data->set.timeout);
  else
    timeout = PR_MillisecondsToInterval(DEFAULT_CONNECT_TIMEOUT);

  nread = PR_Recv(conn->ssl[num].handle, buf, (int)buffersize, 0, timeout);
  *wouldblock = FALSE;
  if(nread < 0) {
    /* failed SSL read */
    PRInt32 err = PR_GetError();

    if(err == PR_WOULD_BLOCK_ERROR) {
      *wouldblock = TRUE;
      return -1; /* basically EWOULDBLOCK */
    }
    if(err == PR_IO_TIMEOUT_ERROR) {
      failf(data, "SSL connection timeout");
      return CURLE_OPERATION_TIMEDOUT;
    }
    failf(conn->data, "SSL read: errno %d", err);
    return -1;
  }
  return nread;
}