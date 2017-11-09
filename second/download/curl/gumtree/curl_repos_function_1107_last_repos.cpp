CURLcode Curl_http2_done_sending(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  if((conn->handler == &Curl_handler_http2_ssl) ||
     (conn->handler == &Curl_handler_http2)) {
    /* make sure this is only attempted for HTTP/2 transfers */

    struct HTTP *stream = conn->data->req.protop;

    if(stream->upload_left) {
      /* If the stream still thinks there's data left to upload. */
      struct http_conn *httpc = &conn->proto.httpc;
      nghttp2_session *h2 = httpc->h2;

      stream->upload_left = 0; /* DONE! */

      /* resume sending here to trigger the callback to get called again so
         that it can signal EOF to nghttp2 */
      (void)nghttp2_session_resume_data(h2, stream->stream_id);

      (void)h2_process_pending_input(conn->data, httpc, &result);
    }
  }
  return result;
}