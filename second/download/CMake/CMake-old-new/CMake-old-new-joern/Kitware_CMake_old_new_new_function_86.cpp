static void hashkey(struct connectdata *conn, char *buf,
                    size_t len) /* something like 128 is fine */
{
  const char *hostname;

  if(conn->bits.socksproxy)
    hostname = conn->socks_proxy.host.name;
  else if(conn->bits.httpproxy)
    hostname = conn->http_proxy.host.name;
  else if(conn->bits.conn_to_host)
    hostname = conn->conn_to_host.name;
  else
    hostname = conn->host.name;

  DEBUGASSERT(len > 32);

  /* put the number first so that the hostname gets cut off if too long */
  snprintf(buf, len, "%ld%s", conn->port, hostname);
}