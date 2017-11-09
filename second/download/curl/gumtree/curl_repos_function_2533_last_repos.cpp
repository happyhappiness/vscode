static CURLcode Curl_cyassl_connect(struct connectdata *conn, int sockindex)
{
  CURLcode result;
  bool done = FALSE;

  result = cyassl_connect_common(conn, sockindex, FALSE, &done);
  if(result)
    return result;

  DEBUGASSERT(done);

  return CURLE_OK;
}