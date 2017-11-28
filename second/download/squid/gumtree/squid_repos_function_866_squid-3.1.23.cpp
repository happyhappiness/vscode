void
commConnectStart(int fd, const char *host, unsigned short port, AsyncCall::Pointer &cb)
{
    debugs(cb->debugSection, cb->debugLevel, "commConnectStart: FD " << fd <<
           ", cb " << cb << ", " << host << ":" << port); // TODO: just print *cb

    ConnectStateData *cs;
    cs = new ConnectStateData;
    cs->fd = fd;
    cs->host = xstrdup(host);
    cs->default_port = port;
    cs->callback = cb;

    comm_add_close_handler(fd, commConnectFree, cs);
    ipcache_nbgethostbyname(host, commConnectDnsHandle, cs);
}