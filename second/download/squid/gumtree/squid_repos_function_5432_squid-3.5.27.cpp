void
Ftp::DataChannel::addr(const Ip::Address &import)
{
    static char addrBuf[MAX_IPSTRLEN];
    import.toStr(addrBuf, sizeof(addrBuf));
    xfree(host);
    host = xstrdup(addrBuf);
    port = import.port();
}