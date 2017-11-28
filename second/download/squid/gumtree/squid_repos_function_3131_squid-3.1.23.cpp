const char *
fqdnFromAddr(IpAddress &addr)
{
    const char *n;
    static char buf[MAX_IPSTRLEN];

    if (Config.onoff.log_fqdn && (n = fqdncache_gethostbyaddr(addr, 0)))
        return n;

/// \todo Perhapse this should use toHostname() instead of straight NtoA.
///       that would wrap the IPv6 properly when raw.
    addr.NtoA(buf, MAX_IPSTRLEN);

    return buf;
}