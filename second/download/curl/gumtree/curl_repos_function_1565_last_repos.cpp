bool Curl_connect_complete(struct connectdata *conn)
{
  return !conn->connect_state ||
    (conn->connect_state->tunnel_state == TUNNEL_COMPLETE);
}