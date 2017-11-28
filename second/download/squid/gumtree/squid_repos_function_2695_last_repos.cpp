char *
internalRemoteUri(const char *host, unsigned short port, const char *dir, const SBuf &name)
{
    static char lc_host[SQUIDHOSTNAMELEN];
    assert(host && !name.isEmpty());
    /* convert host name to lower case */
    xstrncpy(lc_host, host, SQUIDHOSTNAMELEN);
    Tolower(lc_host);

    /* check for an IP address and format appropriately if found */
    Ip::Address test = lc_host;
    if ( !test.isAnyAddr() ) {
        test.toHostStr(lc_host,SQUIDHOSTNAMELEN);
    }

    /*
     * append the domain in order to mirror the requests with appended
     * domains
     */

    /* For IPv6 addresses also check for a colon */
    if (Config.appendDomain && !strchr(lc_host, '.') && !strchr(lc_host, ':'))
        strncat(lc_host, Config.appendDomain, SQUIDHOSTNAMELEN -
                strlen(lc_host) - 1);

    /* build URI */
    URL tmp(AnyP::PROTO_HTTP);
    tmp.host(lc_host);
    if (port)
        tmp.port(port);

    static MemBuf mb;

    mb.reset();
    mb.appendf("http://" SQUIDSBUFPH, SQUIDSBUFPRINT(tmp.authority()));

    if (dir)
        mb.append(dir, strlen(dir));

    mb.append(name.rawContent(), name.length());

    /* return a pointer to a local static buffer */
    return mb.buf;
}