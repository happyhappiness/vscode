static ssize_t gskit_recv(struct connectdata *conn, int num, char *buf,
                           size_t buffersize, CURLcode *curlcode)
{
  struct SessionHandle *data = conn->data;
  int buffsize;
  int nread;
  CURLcode cc;

  buffsize = buffersize > (size_t) INT_MAX? INT_MAX: (int) buffersize;
  cc = gskit_status(data, gsk_secure_soc_read(conn->ssl[num].handle,
                                              buf, buffsize, &nread),
                    "gsk_secure_soc_read()", CURLE_RECV_ERROR);
  if(cc != CURLE_OK) {
    *curlcode = cc;
    nread = -1;
  }
  return (ssize_t) nread;
}