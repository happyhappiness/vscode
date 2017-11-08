static ssize_t send_callback(nghttp2_session *h2,
                             const uint8_t *data, size_t length, int flags,
                             void *userp)
{
  struct connectdata *conn = (struct connectdata *)userp;
  ssize_t written;
  CURLcode rc =
    Curl_write(conn, conn->sock[0], data, length, &written);
  (void)h2;
  (void)flags;

  if(rc) {
    failf(conn->data, "Failed sending HTTP2 data");
    return NGHTTP2_ERR_CALLBACK_FAILURE;
  }
  else if(!written)
    return NGHTTP2_ERR_WOULDBLOCK;

  return written;
}