void Curl_http2_done(struct connectdata *conn, bool premature)
{
  struct Curl_easy *data = conn->data;
  struct HTTP *http = data->req.protop;
  struct http_conn *httpc = &conn->proto.httpc;

  if(http->header_recvbuf) {
    DEBUGF(infof(data, "free header_recvbuf!!\n"));
    Curl_add_buffer_free(http->header_recvbuf);
    http->header_recvbuf = NULL; /* clear the pointer */
    Curl_add_buffer_free(http->trailer_recvbuf);
    http->trailer_recvbuf = NULL; /* clear the pointer */
    if(http->push_headers) {
      /* if they weren't used and then freed before */
      for(; http->push_headers_used > 0; --http->push_headers_used) {
        free(http->push_headers[http->push_headers_used - 1]);
      }
      free(http->push_headers);
      http->push_headers = NULL;
    }
  }

  if(premature) {
    /* RST_STREAM */
    nghttp2_submit_rst_stream(httpc->h2, NGHTTP2_FLAG_NONE, http->stream_id,
                              NGHTTP2_STREAM_CLOSED);
    if(http->stream_id == httpc->pause_stream_id) {
      infof(data, "stopped the pause stream!\n");
      httpc->pause_stream_id = 0;
    }
  }
  if(http->stream_id) {
    nghttp2_session_set_stream_user_data(httpc->h2, http->stream_id, 0);
    http->stream_id = 0;
  }
}