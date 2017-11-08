static int on_begin_headers(nghttp2_session *session,
                            const nghttp2_frame *frame, void *userp)
{
  struct connectdata *conn = (struct connectdata *)userp;
  (void)session;
  (void)frame;
  infof(conn->data, "on_begin_headers() was called\n");
  return 0;
}