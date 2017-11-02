CURLcode Curl_gskit_connect_nonblocking(struct connectdata *conn,
                                        int sockindex,
                                        bool *done)
{
  CURLcode result;

  result = gskit_connect_common(conn, sockindex, TRUE, done);
  if(*done || result)
    conn->ssl[sockindex].connecting_state = ssl_connect_1;
  return result;
}