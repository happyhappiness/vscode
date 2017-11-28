void
mcastJoinGroups(const ipcache_addrs *ia, const DnsLookupDetails &, void *datanotused)
{
#ifdef IP_MULTICAST_TTL
    int fd = theInIcpConnection;

    struct ip_mreq mr;
    int i;
    int x;
    char c = 0;

    if (ia == NULL) {
        debugs(7, 0, "comm_join_mcast_groups: Unknown host");
        return;
    }

    for (i = 0; i < (int) ia->count; i++) {
        debugs(7, 9, "Listening for ICP requests on " << ia->in_addrs[i] );

        if ( ! ia->in_addrs[i].IsIPv4() ) {
            debugs(7, 9, "ERROR: IPv6 Multicast Listen has not been implemented!");
            continue;
        }

        ia->in_addrs[i].GetInAddr(mr.imr_multiaddr);

        mr.imr_interface.s_addr = INADDR_ANY;
        x = setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                       (char *) &mr, sizeof(struct ip_mreq));

        if (x < 0)
            debugs(7, 1, "comm_join_mcast_groups: FD " << fd << ", IP=" << ia->in_addrs[i]);

        x = setsockopt(fd, IPPROTO_IP, IP_MULTICAST_LOOP, &c, 1);

        if (x < 0)
            debugs(7, 1, "Can't disable multicast loopback: " << xstrerror());
    }

#endif
}