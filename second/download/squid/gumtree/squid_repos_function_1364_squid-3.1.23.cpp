void
icpConnectionsOpen(void)
{
    u_int16_t port;

    IpAddress addr;

    struct addrinfo *xai = NULL;
    int x;
    wordlist *s;

    if ((port = Config.Port.icp) <= 0)
        return;

    enter_suid();

    addr = Config.Addrs.udp_incoming;
    addr.SetPort(port);

    if (!Ip::EnableIpv6 && !addr.SetIPv4()) {
        debugs(12, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << addr << " is not an IPv4 address.");
        fatal("ICP port cannot be opened.");
    }
    /* split-stack for now requires default IPv4-only ICP */
    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && addr.IsAnyAddr()) {
        addr.SetIPv4();
    }

    theInIcpConnection = comm_open_listener(SOCK_DGRAM,
                                            IPPROTO_UDP,
                                            addr,
                                            COMM_NONBLOCKING,
                                            "ICP Socket");
    leave_suid();

    if (theInIcpConnection < 0)
        fatal("Cannot open ICP Port");

    commSetSelect(theInIcpConnection,
                  COMM_SELECT_READ,
                  icpHandleUdp,
                  NULL,
                  0);

    for (s = Config.mcast_group_list; s; s = s->next)
        ipcache_nbgethostbyname(s->key, mcastJoinGroups, NULL);

    debugs(12, 1, "Accepting ICP messages at " << addr << ", FD " << theInIcpConnection << ".");

    addr.SetEmpty(); // clear for next use.
    addr = Config.Addrs.udp_outgoing;
    if ( !addr.IsNoAddr() ) {
        enter_suid();
        addr.SetPort(port);

        if (!Ip::EnableIpv6 && !addr.SetIPv4()) {
            debugs(49, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << addr << " is not an IPv4 address.");
            fatal("ICP port cannot be opened.");
        }
        /* split-stack for now requires default IPv4-only ICP */
        if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && addr.IsAnyAddr()) {
            addr.SetIPv4();
        }

        theOutIcpConnection = comm_open_listener(SOCK_DGRAM,
                              IPPROTO_UDP,
                              addr,
                              COMM_NONBLOCKING,
                              "ICP Port");
        leave_suid();

        if (theOutIcpConnection < 0)
            fatal("Cannot open Outgoing ICP Port");

        commSetSelect(theOutIcpConnection,
                      COMM_SELECT_READ,
                      icpHandleUdp,
                      NULL,
                      0);

        debugs(12, 1, "Outgoing ICP messages on port " << addr.GetPort() << ", FD " << theOutIcpConnection << ".");

        fd_note(theOutIcpConnection, "Outgoing ICP socket");

        fd_note(theInIcpConnection, "Incoming ICP socket");
    } else {
        theOutIcpConnection = theInIcpConnection;
    }

    theOutICPAddr.SetEmpty();

    theOutICPAddr.InitAddrInfo(xai);

    x = getsockname(theOutIcpConnection, xai->ai_addr, &xai->ai_addrlen);

    if (x < 0)
        debugs(50, 1, "theOutIcpConnection FD " << theOutIcpConnection << ": getsockname: " << xstrerror());
    else
        theOutICPAddr = *xai;

    theOutICPAddr.FreeAddrInfo(xai);
}