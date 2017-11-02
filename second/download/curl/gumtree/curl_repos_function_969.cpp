CURLcode Curl_http2_setup(struct connectdata *conn)
{
  struct http_conn *httpc = &conn->proto.httpc;
  if(conn->handler->flags & PROTOPT_SSL)
    conn->handler = &Curl_handler_http2_ssl;
  else
    conn->handler = &Curl_handler_http2;

  infof(conn->data, "Using HTTP2\n");
  httpc->bodystarted = FALSE;
  httpc->closed = FALSE;
  httpc->header_recvbuf = Curl_add_buffer_init();
  httpc->nread_header_recvbuf = 0;
  httpc->data = NULL;
  httpc->datalen = 0;
  httpc->upload_left = 0;
  httpc->upload_mem = NULL;
  httpc->upload_len = 0;
  httpc->stream_id = -1;
  httpc->status_code = -1;

  conn->httpversion = 20;

  return 0;
}