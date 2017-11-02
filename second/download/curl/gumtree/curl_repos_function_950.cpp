static CURLcode http2_disconnect(struct connectdata *conn,
                                 bool dead_connection)
{
  struct http_conn *httpc = &conn->proto.httpc;
  (void)dead_connection;

  infof(conn->data, "HTTP/2 DISCONNECT starts now\n");

  nghttp2_session_del(httpc->h2);

  Curl_safefree(httpc->header_recvbuf->buffer);
  Curl_safefree(httpc->header_recvbuf);

  Curl_safefree(httpc->inbuf);

  infof(conn->data, "HTTP/2 DISCONNECT done\n");

  return CURLE_OK;
}