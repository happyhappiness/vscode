CURLcode Curl_proxyCONNECT(struct connectdata *conn,
                           int sockindex,
                           const char *hostname,
                           int remote_port)
{
  CURLcode result;
  if(!conn->connect_state) {
    result = connect_init(conn, FALSE);
    if(result)
      return result;
  }
  result = CONNECT(conn, sockindex, hostname, remote_port);

  if(result || Curl_connect_complete(conn))
    connect_done(conn);

  return result;
}