
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

/*
 * makes internal url with local host and port
 */
char *
internalLocalUri(const char *dir, const SBuf &name)
{
    return internalRemoteUri(getMyHostname(),
                             getMyPort(), dir, name);
}

const char *
