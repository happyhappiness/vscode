int Curl_nss_send(struct connectdata *conn,  /* connection data */
                  int sockindex,             /* socketindex */
                  void *mem,                 /* send this data */
                  size_t len)                /* amount to write */
{
  PRInt32 err;
  struct SessionHandle *data = conn->data;
  PRInt32 timeout;
  int rc;

  if(data->set.timeout)
    timeout = PR_MillisecondsToInterval(data->set.timeout);
  else
    timeout = PR_MillisecondsToInterval(DEFAULT_CONNECT_TIMEOUT);

  rc = PR_Send(conn->ssl[sockindex].handle, mem, (int)len, 0, timeout);

  if(rc < 0) {
    err = PR_GetError();

    if(err == PR_IO_TIMEOUT_ERROR) {
      failf(data, "SSL connection timeout");
      return CURLE_OPERATION_TIMEDOUT;
    }

    failf(conn->data, "SSL write: error %d", err);
    return -1;
  }
  return rc; /* number of bytes */
}