/* returns an allocated key to find a bundle for this connection */
static char *hashkey(struct connectdata *conn)
{
  return aprintf("%s:%d",
                 conn->bits.proxy?conn->proxy.name:conn->host.name,
                 conn->localport);
}

/* Look up the bundle with all the connections to the same host this
