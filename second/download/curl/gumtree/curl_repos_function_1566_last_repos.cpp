bool Curl_connect_ongoing(struct connectdata *conn)
{
  return conn->connect_state &&
    (conn->connect_state->tunnel_state != TUNNEL_COMPLETE);
}