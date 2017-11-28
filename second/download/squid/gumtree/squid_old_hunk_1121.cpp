
    /* For IPv6 addresses also check for a colon */
    if (Config.appendDomain && !strchr(lc_host, '.') && !strchr(lc_host, ':'))
        strncat(lc_host, Config.appendDomain, SQUIDHOSTNAMELEN -
                strlen(lc_host) - 1);

    /* build uri in mb */
    static MemBuf mb;

    mb.reset();

    mb.Printf("http://%s", lc_host);

    /* append port if not default */
    if (port && port != urlDefaultPort(AnyP::PROTO_HTTP))
        mb.Printf(":%d", port);

    if (dir)
        mb.Printf("%s", dir);

    mb.Printf("%s", name);

    /* return a pointer to a local static buffer */
    return mb.buf;
}

/*
 * makes internal url with local host and port
 */
char *
internalLocalUri(const char *dir, const char *name)
{
    return internalRemoteUri(getMyHostname(),
                             getMyPort(), dir, name);
}

const char *
