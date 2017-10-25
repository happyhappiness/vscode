static CURLcode expect100(struct SessionHandle *data,
                          send_buffer *req_buffer)
{
  CURLcode result = CURLE_OK;
  if((data->set.httpversion != CURL_HTTP_VERSION_1_0) &&
     !checkheaders(data, "Expect:")) {
    /* if not doing HTTP 1.0 or disabled explicitly, we add a Expect:
       100-continue to the headers which actually speeds up post
       operations (as there is one packet coming back from the web
       server) */
    result = add_bufferf(req_buffer,
                         "Expect: 100-continue\r\n");
    if(result == CURLE_OK)
      data->set.expect100header = TRUE;
  }
  return result;
}