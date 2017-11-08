static void verboseconnect(struct connectdata *conn)
{
  infof(conn->data, "Connected to %s (%s) port %d\n",
        conn->bits.httpproxy ? conn->proxy.dispname : conn->host.dispname,
        conn->ip_addr_str, conn->port);
}