char *
internalRemoteUri(const char *host, unsigned short port, const char *dir, const char *name)
{
    static char lc_host[SQUIDHOSTNAMELEN];
    assert(host && name);
    /* convert host name to lower case */
    xstrncpy(lc_host, host, SQUIDHOSTNAMELEN);
    Tolower(lc_host);

    /* check for an IP address and format appropriately if found */
    IpAddress test = lc_host;
    if ( !test.IsAnyAddr() ) {
        test.ToHostname(lc_host,SQUIDHOSTNAMELEN);
    }

    /*
     * append the domain in order to mirror the requests with appended
     * domains
     */

    /* For IPv6 addresses also check for a colon */
    if (Config.appendDomain && !strchr(lc_host, '.') && !strchr(lc_host, ':'))
        strncat(lc_host, Config.appendDomain, SQUIDHOSTNAMELEN -
                strlen(lc_host) - 1);

    /* build uri in mb */
    static MemBuf mb;

    mb.reset();

    mb.Printf("http://%s", lc_host);

    /* append port if not default */
    if (port && port != urlDefaultPort(PROTO_HTTP))
        mb.Printf(":%d", port);

    if (dir)
        mb.Printf("%s", dir);

    mb.Printf("%s", name);

    /* return a pointer to a local static buffer */
    return mb.buf;
}