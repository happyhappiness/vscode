static int should_close_session(struct http_conn *httpc)
{
  return httpc->drain_total == 0 && !nghttp2_session_want_read(httpc->h2) &&
    !nghttp2_session_want_write(httpc->h2);
}