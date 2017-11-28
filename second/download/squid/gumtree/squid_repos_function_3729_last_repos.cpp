bool
Ftp::ParseProtoIpPort(const char *buf, Ip::Address &addr)
{

    const char delim = *buf;
    const char *s = buf + 1;
    const char *e = s;
    const int proto = strtol(s, const_cast<char**>(&e), 10);
    if ((proto != 1 && proto != 2) || *e != delim)
        return false;

    s = e + 1;
    e = strchr(s, delim);
    char ip[MAX_IPSTRLEN];
    if (static_cast<size_t>(e - s) >= sizeof(ip))
        return false;
    strncpy(ip, s, e - s);
    ip[e - s] = '\0';
    addr = ip;

    if (addr.isAnyAddr())
        return false;

    if ((proto == 2) != addr.isIPv6()) // proto ID mismatches address version
        return false;

    s = e + 1; // skip port delimiter
    const int port = strtol(s, const_cast<char**>(&e), 10);
    if (port < 0 || *e != '|')
        return false;

    if (Config.Ftp.sanitycheck && port < 1024)
        return false;

    addr.port(port);
    return true;
}