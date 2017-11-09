void Curl_http2_setup_req(struct Curl_easy *data)
{
  struct HTTP *http = data->req.protop;

  http->nread_header_recvbuf = 0;
  http->bodystarted = FALSE;
  http->status_code = -1;
  http->pausedata = NULL;
  http->pauselen = 0;
  http->error_code = NGHTTP2_NO_ERROR;
  http->closed = FALSE;
  http->close_handled = FALSE;
  http->mem = data->state.buffer;
  http->len = data->set.buffer_size;
  http->memlen = 0;
}