static char *hashkey(struct connectdata *conn)
{
  const char *hostname;

  if(conn->bits.proxy)
    hostname = conn->proxy.name;
  else if(conn->bits.conn_to_host)
    hostname = conn->conn_to_host.name;
  else
    hostname = conn->host.name;

  return aprintf("%s:%d", hostname, conn->port);
}