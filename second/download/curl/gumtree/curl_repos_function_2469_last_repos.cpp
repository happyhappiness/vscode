static CURLcode Curl_schannel_connect(struct connectdata *conn, int sockindex)
{
  CURLcode result;
  bool done = FALSE;

  result = schannel_connect_common(conn, sockindex, FALSE, &done);
  if(result)
    return result;

  DEBUGASSERT(done);

  return CURLE_OK;
}