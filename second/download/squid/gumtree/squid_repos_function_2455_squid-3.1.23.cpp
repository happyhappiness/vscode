static void
send_announce(const ipcache_addrs *ia, const DnsLookupDetails &, void *junk)
{
    LOCAL_ARRAY(char, tbuf, 256);
    LOCAL_ARRAY(char, sndbuf, BUFSIZ);

    IpAddress S;
    char *host = Config.Announce.host;
    char *file = NULL;
    unsigned short port = Config.Announce.port;
    int l;
    int n;
    int fd;
    int x;

    if (ia == NULL) {
        debugs(27, 1, "send_announce: Unknown host '" << host << "'");
        return;
    }

    debugs(27, 1, "Sending Announcement to " << host);
    sndbuf[0] = '\0';
    snprintf(tbuf, 256, "cache_version SQUID/%s\n", version_string);
    strcat(sndbuf, tbuf);
    assert(Config.Sockaddr.http);
    snprintf(tbuf, 256, "Running on %s %d %d\n",
             getMyHostname(),
             getMyPort(),
             (int) Config.Port.icp);
    strcat(sndbuf, tbuf);

    if (Config.adminEmail) {
        snprintf(tbuf, 256, "cache_admin: %s\n", Config.adminEmail);
        strcat(sndbuf, tbuf);
    }

    snprintf(tbuf, 256, "generated %d [%s]\n",
             (int) squid_curtime,
             mkhttpdlogtime(&squid_curtime));
    strcat(sndbuf, tbuf);
    l = strlen(sndbuf);

    if ((file = Config.Announce.file) != NULL) {
        fd = file_open(file, O_RDONLY | O_TEXT);

        if (fd > -1 && (n = FD_READ_METHOD(fd, sndbuf + l, BUFSIZ - l - 1)) > 0) {
            fd_bytes(fd, n, FD_READ);
            l += n;
            sndbuf[l] = '\0';
            file_close(fd);
        } else {
            debugs(50, 1, "send_announce: " << file << ": " << xstrerror());
        }
    }

    S = ia->in_addrs[0];
    S.SetPort(port);
    assert(theOutIcpConnection > 0);
    x = comm_udp_sendto(theOutIcpConnection, S, sndbuf, strlen(sndbuf) + 1);

    if (x < 0)
        debugs(27, 1, "send_announce: FD " << theOutIcpConnection << ": " << xstrerror());
}