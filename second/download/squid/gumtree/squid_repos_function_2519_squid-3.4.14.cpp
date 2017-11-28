static void
send_announce(const ipcache_addrs *ia, const DnsLookupDetails &, void *junk)
{
    LOCAL_ARRAY(char, tbuf, 256);
    LOCAL_ARRAY(char, sndbuf, BUFSIZ);

    char *host = Config.Announce.host;
    char *file = NULL;
    unsigned short port = Config.Announce.port;
    int l;
    int n;
    int fd;

    if (ia == NULL) {
        debugs(27, DBG_IMPORTANT, "send_announce: Unknown host '" << host << "'");
        return;
    }

    debugs(27, DBG_IMPORTANT, "Sending Announcement to " << host);
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
             Time::FormatHttpd(squid_curtime));
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
            debugs(50, DBG_IMPORTANT, "send_announce: " << file << ": " << xstrerror());
        }
    }

    Ip::Address S = ia->in_addrs[0];
    S.port(port);
    assert(Comm::IsConnOpen(icpOutgoingConn));

    if (comm_udp_sendto(icpOutgoingConn->fd, S, sndbuf, strlen(sndbuf) + 1) < 0)
        debugs(27, DBG_IMPORTANT, "ERROR: Failed to announce to " << S << " from " << icpOutgoingConn->local << ": " << xstrerror());
}