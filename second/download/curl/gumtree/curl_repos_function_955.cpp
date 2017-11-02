static int on_data_chunk_recv(nghttp2_session *session, uint8_t flags,
                              int32_t stream_id,
                              const uint8_t *data, size_t len, void *userp)
{
  struct connectdata *conn = (struct connectdata *)userp;
  struct http_conn *c = &conn->proto.httpc;
  size_t nread;
  (void)session;
  (void)flags;
  (void)data;
  infof(conn->data, "on_data_chunk_recv() "
        "len = %u, stream = %x\n", len, stream_id);

  if(stream_id != c->stream_id) {
    return 0;
  }

  nread = c->len < len ? c->len : len;
  memcpy(c->mem, data, nread);

  c->mem += nread;
  c->len -= nread;

  infof(conn->data, "%zu data written\n", nread);

  if(nread < len) {
    c->data = data + nread;
    c->datalen = len - nread;
    return NGHTTP2_ERR_PAUSE;
  }
  return 0;
}