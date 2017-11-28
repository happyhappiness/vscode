void
mcastJoinGroups(const ipcache_addrs *ia, const DnsLookupDetails &, void *datanotused)
{
#ifdef IP_MULTICAST_TTL
    struct ip_mreq mr;
    int i;

    if (ia == NULL) {
        debugs(7, DBG_CRITICAL, "comm_join_mcast_groups: Unknown host");
        return;
    }

    for (i = 0; i < (int) ia->count; ++i) {
        debugs(7, 9, "Listening for ICP requests on " << ia->in_addrs[i] );

        if ( ! ia->in_addrs[i].IsIPv4() ) {
            debugs(7, 9, "ERROR: IPv6 Multicast Listen has not been implemented!");
            continue;
        }

        ia->in_addrs[i].GetInAddr(mr.imr_multiaddr);

        mr.imr_interface.s_addr = INADDR_ANY;

        if (setsockopt(icpIncomingConn->fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &mr, sizeof(struct ip_mreq)) < 0)
            debugs(7, DBG_IMPORTANT, "ERROR: Join failed for " << icpIncomingConn << ", Multicast IP=" << ia->in_addrs[i]);

        char c = 0;
        if (setsockopt(icpIncomingConn->fd, IPPROTO_IP, IP_MULTICAST_LOOP, &c, 1) < 0)
            debugs(7, DBG_IMPORTANT, "ERROR: " << icpIncomingConn << " can't disable multicast loopback: " << xstrerror());
    }

#endif
}