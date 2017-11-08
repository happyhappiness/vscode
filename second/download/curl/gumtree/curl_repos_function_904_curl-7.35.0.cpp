static ssize_t recv_callback(nghttp2_session *h2,
                             uint8_t *buf, size_t length, int flags,
                             void *userp)
{
  struct connectdata *conn = (struct connectdata *)userp;
  ssize_t nread;
  CURLcode rc = Curl_read(conn, conn->sock[0], (char *)buf, length, &nread);
  (void)h2;
  (void)flags;

  if(rc) {
    failf(conn->data, "Failed recving HTTP2 data");
    return NGHTTP2_ERR_CALLBACK_FAILURE;
  }
  if(!nread)
    return NGHTTP2_ERR_WOULDBLOCK;

  return nread;
}