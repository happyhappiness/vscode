CURLcode Curl_http_setup_conn(struct connectdata *conn)
{
  /* allocate the HTTP-specific struct for the Curl_easy, only to survive
     during this request */
  struct HTTP *http;
  DEBUGASSERT(conn->data->req.protop == NULL);

  http = calloc(1, sizeof(struct HTTP));
  if(!http)
    return CURLE_OUT_OF_MEMORY;

  Curl_mime_initpart(&http->form, conn->data);
  conn->data->req.protop = http;

  Curl_http2_setup_conn(conn);
  Curl_http2_setup_req(conn->data);

  return CURLE_OK;
}