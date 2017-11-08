static int on_stream_close(nghttp2_session *session, int32_t stream_id,
                           uint32_t error_code, void *userp)
{
  struct connectdata *conn = (struct connectdata *)userp;
  struct http_conn *c = &conn->proto.httpc;
  (void)session;
  (void)stream_id;
  infof(conn->data, "on_stream_close() was called, error_code = %d\n",
        error_code);

  if(stream_id != c->stream_id) {
    return 0;
  }

  c->closed = TRUE;

  return 0;
}