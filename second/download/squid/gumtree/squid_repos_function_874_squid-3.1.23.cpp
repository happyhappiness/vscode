static void
commReconnect(void *data)
{
    ConnectStateData *cs = (ConnectStateData *)data;
    ipcache_nbgethostbyname(cs->host, commConnectDnsHandle, cs);
}