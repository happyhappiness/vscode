static void connect_done(struct connectdata *conn)
{
  struct http_connect_state *s = conn->connect_state;
  s->tunnel_state = TUNNEL_COMPLETE;
  infof(conn->data, "CONNECT phase completed!\n");
}