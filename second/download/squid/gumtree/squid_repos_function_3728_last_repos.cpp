bool
Ftp::ParseIpPort(const char *buf, const char *forceIp, Ip::Address &addr)
{
    int h1, h2, h3, h4;
    int p1, p2;
    const int n = sscanf(buf, "%d,%d,%d,%d,%d,%d",
                         &h1, &h2, &h3, &h4, &p1, &p2);

    if (n != 6 || p1 < 0 || p2 < 0 || p1 > 255 || p2 > 255)
        return false;

    if (forceIp) {
        addr = forceIp; // but the above code still validates the IP we got
    } else {
        static char ipBuf[1024];
        snprintf(ipBuf, sizeof(ipBuf), "%d.%d.%d.%d", h1, h2, h3, h4);
        addr = ipBuf;

        if (addr.isAnyAddr())
            return false;
    }

    const int port = ((p1 << 8) + p2);

    if (port <= 0)
        return false;

    if (Config.Ftp.sanitycheck && port < 1024)
        return false;

    addr.port(port);
    return true;
}