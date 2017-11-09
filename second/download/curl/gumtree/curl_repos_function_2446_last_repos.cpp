static ssize_t gskit_recv(struct connectdata *conn, int num, char *buf,
                           size_t buffersize, CURLcode *curlcode)
{
  struct ssl_connect_data *connssl = &conn->ssl[num];
  struct Curl_easy *data = conn->data;
  int buffsize;
  int nread;
  CURLcode cc = CURLE_RECV_ERROR;

  if(pipe_ssloverssl(conn, num, SOS_READ) >= 0) {
    buffsize = buffersize > (size_t) INT_MAX? INT_MAX: (int) buffersize;
    cc = gskit_status(data, gsk_secure_soc_read(BACKEND->handle,
                                                buf, buffsize, &nread),
                      "gsk_secure_soc_read()", CURLE_RECV_ERROR);
  }
  switch(cc) {
  case CURLE_OK:
    break;
  case CURLE_OPERATION_TIMEDOUT:
    cc = CURLE_AGAIN;
  default:
    *curlcode = cc;
    nread = -1;
    break;
  }
  return (ssize_t) nread;
}