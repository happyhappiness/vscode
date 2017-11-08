static CURLcode http2_disconnect(struct connectdata *conn,
                                 bool dead_connection)
{
  struct http_conn *c = &conn->proto.httpc;
  (void)dead_connection;

  DEBUGF(infof(conn->data, "HTTP/2 DISCONNECT starts now\n"));

  nghttp2_session_del(c->h2);
  Curl_safefree(c->inbuf);
  http2_stream_free(conn->data->req.protop);

  DEBUGF(infof(conn->data, "HTTP/2 DISCONNECT done\n"));

  return CURLE_OK;
}