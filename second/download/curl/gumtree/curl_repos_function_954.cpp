static int on_invalid_frame_recv(nghttp2_session *session,
                                 const nghttp2_frame *frame,
                                 uint32_t error_code, void *userp)
{
  struct connectdata *conn = (struct connectdata *)userp;
  (void)session;
  (void)frame;
  infof(conn->data, "on_invalid_frame_recv() was called, error_code = %d\n",
        error_code);
  return 0;
}