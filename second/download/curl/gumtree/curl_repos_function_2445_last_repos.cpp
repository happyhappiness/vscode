static ssize_t gskit_send(struct connectdata *conn, int sockindex,
                           const void *mem, size_t len, CURLcode *curlcode)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct Curl_easy *data = conn->data;
  CURLcode cc = CURLE_SEND_ERROR;
  int written;

  if(pipe_ssloverssl(conn, sockindex, SOS_WRITE) >= 0) {
    cc = gskit_status(data,
                      gsk_secure_soc_write(BACKEND->handle,
                                           (char *) mem, (int) len, &written),
                      "gsk_secure_soc_write()", CURLE_SEND_ERROR);
    if(cc == CURLE_OK)
      if(pipe_ssloverssl(conn, sockindex, SOS_WRITE) < 0)
        cc = CURLE_SEND_ERROR;
  }
  if(cc != CURLE_OK) {
    *curlcode = cc;
    written = -1;
  }
  return (ssize_t) written; /* number of bytes */
}