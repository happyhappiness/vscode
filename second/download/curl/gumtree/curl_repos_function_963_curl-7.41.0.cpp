static ssize_t data_source_read_callback(nghttp2_session *session,
                                         int32_t stream_id,
                                         uint8_t *buf, size_t length,
                                         uint32_t *data_flags,
                                         nghttp2_data_source *source,
                                         void *userp)
{
  struct connectdata *conn = (struct connectdata *)userp;
  struct http_conn *c = &conn->proto.httpc;
  size_t nread;
  (void)session;
  (void)stream_id;
  (void)source;

  nread = c->upload_len < length ? c->upload_len : length;
  if(nread > 0) {
    memcpy(buf, c->upload_mem, nread);
    c->upload_mem += nread;
    c->upload_len -= nread;
    c->upload_left -= nread;
  }

  if(c->upload_left == 0)
    *data_flags = 1;
  else if(nread == 0)
    return NGHTTP2_ERR_DEFERRED;

  return nread;
}