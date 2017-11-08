static CURLcode http2_disconnect(struct connectdata *conn,
                                 bool dead_connection)
{
  struct HTTP *http = conn->data->req.protop;
  struct http_conn *c = &conn->proto.httpc;
  (void)dead_connection;

  DEBUGF(infof(conn->data, "HTTP/2 DISCONNECT starts now\n"));

  nghttp2_session_del(c->h2);
  Curl_safefree(c->inbuf);

  if(http) {
    Curl_add_buffer_free(http->header_recvbuf);
    http->header_recvbuf = NULL; /* clear the pointer */
    Curl_add_buffer_free(http->trailer_recvbuf);
    http->trailer_recvbuf = NULL; /* clear the pointer */
    for(; http->push_headers_used > 0; --http->push_headers_used) {
      free(http->push_headers[http->push_headers_used - 1]);
    }
    free(http->push_headers);
    http->push_headers = NULL;
  }

  DEBUGF(infof(conn->data, "HTTP/2 DISCONNECT done\n"));

  return CURLE_OK;
}