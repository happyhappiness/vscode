static char *hashkey(struct connectdata *conn)
{
  return aprintf("%s:%d",
                 conn->bits.proxy?conn->proxy.name:conn->host.name,
                 conn->localport);
}