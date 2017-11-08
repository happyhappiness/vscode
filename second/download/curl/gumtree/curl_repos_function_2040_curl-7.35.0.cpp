CURLcode Curl_gskit_connect(struct connectdata *conn, int sockindex)
{
  CURLcode retcode;
  bool done;

  conn->ssl[sockindex].connecting_state = ssl_connect_1;
  retcode = gskit_connect_common(conn, sockindex, FALSE, &done);
  if(retcode)
    return retcode;

  DEBUGASSERT(done);

  return CURLE_OK;
}