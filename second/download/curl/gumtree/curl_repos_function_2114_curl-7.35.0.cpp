CURLcode
Curl_schannel_connect(struct connectdata *conn, int sockindex)
{
  CURLcode retcode;
  bool done = FALSE;

  retcode = schannel_connect_common(conn, sockindex, FALSE, &done);
  if(retcode)
    return retcode;

  DEBUGASSERT(done);

  return CURLE_OK;
}