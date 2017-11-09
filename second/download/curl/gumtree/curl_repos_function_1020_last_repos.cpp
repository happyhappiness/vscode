bool Curl_conn_data_pending(struct connectdata *conn, int sockindex)
{
  int readable;

  if(Curl_ssl_data_pending(conn, sockindex) ||
     Curl_recv_has_postponed_data(conn, sockindex))
    return true;

  readable = SOCKET_READABLE(conn->sock[sockindex], 0);
  return (readable > 0 && (readable & CURL_CSELECT_IN));
}