{
  CURLcode result;
  struct http_conn *httpc = &conn->proto.httpc;
  struct HTTP *stream = conn->data->req.protop;

  stream->stream_id = -1;

  if(!stream->header_recvbuf)
    stream->header_recvbuf = Curl_add_buffer_init();

  if((conn->handler == &Curl_handler_http2_ssl) ||
     (conn->handler == &Curl_handler_http2))
    return CURLE_OK; /* already done */

  if(conn->handler->flags & PROTOPT_SSL)
    conn->handler = &Curl_handler_http2_ssl;
  else
    conn->handler = &Curl_handler_http2;

  result = Curl_http2_init(conn);
  if(result)
    return result;

  infof(conn->data, "Using HTTP2, server supports multi-use\n");
  stream->upload_left = 0;
  stream->upload_mem = NULL;
  stream->upload_len = 0;

  httpc->inbuflen = 0;
  httpc->nread_inbuf = 0;

  httpc->pause_stream_id = 0;
  httpc->drain_total = 0;

  conn->bits.multiplex = TRUE; /* at least potentially multiplexed */
  conn->httpversion = 20;
  conn->bundle->multiuse = BUNDLE_MULTIPLEX;

  infof(conn->data, "Connection state changed (HTTP/2 confirmed)\n");
  Curl_multi_connchanged(conn->data->multi);

  return CURLE_OK;
}