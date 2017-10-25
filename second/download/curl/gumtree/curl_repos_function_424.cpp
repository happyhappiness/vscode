CURLcode Curl_protocol_connecting(struct connectdata *conn, bool *done)
{
  CURLcode result=CURLE_OK;

  if(conn && conn->curl_connecting) {
    *done = FALSE;
    result = conn->curl_connecting(conn, done);
  }
  else
    *done = TRUE;

  return result;
}