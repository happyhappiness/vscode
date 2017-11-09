static int error_callback(nghttp2_session *session,
                          const char *msg,
                          size_t len,
                          void *userp)
{
  struct connectdata *conn = (struct connectdata *)userp;
  (void)session;
  infof(conn->data, "http2 error: %.*s\n", len, msg);
  return 0;
}