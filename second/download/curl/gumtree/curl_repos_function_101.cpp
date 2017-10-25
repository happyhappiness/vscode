CURLcode curl_done(CURLconnect *c_connect)
{
  struct connectdata *conn = c_connect;
  struct UrlData *data;
  CURLcode result;

  if(!conn || (conn->handle!= STRUCT_CONNECT)) {
    return CURLE_BAD_FUNCTION_ARGUMENT;
  }
  if(conn->state != CONN_DO) {
    /* This can only be called after a curl_do() */
    return CURLE_BAD_CALLING_ORDER;
  }
  data = conn->data;

  /* this calls the protocol-specific function pointer previously set */
  if(conn->curl_done)
    result = conn->curl_done(conn);
  else
    result = CURLE_OK;

  pgrsDone(data); /* done with the operation */

  conn->state = CONN_DONE;

  return result;
}