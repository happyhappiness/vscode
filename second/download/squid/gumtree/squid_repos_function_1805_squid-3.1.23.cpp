static int
peerProbeConnect(peer * p)
{
    int fd;
    time_t ctimeout = p->connect_timeout > 0 ? p->connect_timeout
                      : Config.Timeout.peer_connect;
    int ret = squid_curtime - p->stats.last_connect_failure > ctimeout * 10;

    if (p->test_fd != -1)
        return ret;/* probe already running */

    if (squid_curtime - p->stats.last_connect_probe == 0)
        return ret;/* don't probe to often */

    IpAddress temp(getOutgoingAddr(NULL,p));

    // if IPv6 is disabled try to force IPv4-only outgoing.
    if (!Ip::EnableIpv6 && !temp.SetIPv4()) {
        debugs(50, DBG_IMPORTANT, "WARNING: IPv6 is disabled. Failed to use " << temp << " to probe " << p->host);
        return ret;
    }

    // if IPv6 is split-stack, prefer IPv4
    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK) {
        // NP: This is not a great choice of default,
        // but with the current Internet being IPv4-majority has a higher success rate.
        // if setting to IPv4 fails we dont care, that just means to use IPv6 outgoing.
        temp.SetIPv4();
    }

    fd = comm_open(SOCK_STREAM, IPPROTO_TCP, temp, COMM_NONBLOCKING, p->host);

    if (fd < 0)
        return ret;

    comm_add_close_handler(fd, &peerProbeClosed, p);
    commSetTimeout(fd, ctimeout, peerProbeConnectTimeout, p);

    p->test_fd = fd;

    p->stats.last_connect_probe = squid_curtime;

    commConnectStart(p->test_fd,
                     p->host,
                     p->http_port,
                     peerProbeConnectDone,
                     p);

    return ret;
}