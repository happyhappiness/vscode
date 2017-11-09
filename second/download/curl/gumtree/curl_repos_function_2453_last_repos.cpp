static CURLcode Curl_gskit_connect(struct connectdata *conn, int sockindex)
{
  CURLcode result;
  bool done;

  conn->ssl[sockindex].connecting_state = ssl_connect_1;
  result = gskit_connect_common(conn, sockindex, FALSE, &done);
  if(result)
    return result;

  DEBUGASSERT(done);

  return CURLE_OK;
}