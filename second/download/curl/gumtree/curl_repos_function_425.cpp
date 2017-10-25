CURLcode Curl_protocol_doing(struct connectdata *conn, bool *done)
{
  CURLcode result=CURLE_OK;

  if(conn && conn->curl_doing) {
    *done = FALSE;
    result = conn->curl_doing(conn, done);
  }
  else
    *done = TRUE;

  return result;
}