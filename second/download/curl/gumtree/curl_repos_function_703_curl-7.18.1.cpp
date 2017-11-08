static void verboseconnect(struct connectdata *conn)
{
  infof(conn->data, "Connected to %s (%s) port %d (#%d)\n",
        conn->bits.proxy ? conn->proxy.dispname : conn->host.dispname,
        conn->ip_addr_str, conn->port, conn->connectindex);
}