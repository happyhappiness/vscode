static CURLcode connect_init(struct connectdata *conn, bool reinit)
{
  struct http_connect_state *s;
  if(!reinit) {
    DEBUGASSERT(!conn->connect_state);
    s = calloc(1, sizeof(struct http_connect_state));
    if(!s)
      return CURLE_OUT_OF_MEMORY;
    infof(conn->data, "allocate connect buffer!\n");
    conn->connect_state = s;
  }
  else {
    DEBUGASSERT(conn->connect_state);
    s = conn->connect_state;
  }
  s->tunnel_state = TUNNEL_INIT;
  s->keepon = TRUE;
  s->line_start = s->connect_buffer;
  s->ptr = s->line_start;
  s->cl = 0;
  return CURLE_OK;
}