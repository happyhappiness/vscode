void
wccpConnectionOpen(void)
{
    debugs(80, 5, "wccpConnectionOpen: Called");

    if (Config.Wccp.router.IsAnyAddr()) {
        debugs(80, 2, "WCCPv1 disabled.");
        return;
    }

    if ( !Config.Wccp.router.SetIPv4() ) {
        debugs(80, DBG_CRITICAL, "WCCPv1 Disabled. Router " << Config.Wccp.router << " is not an IPv4 address.");
        return;
    }

    if ( !Config.Wccp.address.SetIPv4() ) {
        debugs(80, DBG_CRITICAL, "WCCPv1 Disabled. Local address " << Config.Wccp.address << " is not an IPv4 address.");
        return;
    }

    Config.Wccp.address.SetPort(WCCP_PORT);
    Config.Wccp.router.SetPort(WCCP_PORT);

    theWccpConnection = comm_open_listener(SOCK_DGRAM,
                                           IPPROTO_UDP,
                                           Config.Wccp.address,
                                           COMM_NONBLOCKING,
                                           "WCCP Socket");

    if (theWccpConnection < 0)
        fatal("Cannot open WCCP Port");

    Comm::SetSelect(theWccpConnection, COMM_SELECT_READ, wccpHandleUdp, NULL, 0);

    debugs(80, DBG_IMPORTANT, "Accepting WCCPv1 messages on " << Config.Wccp.address << ", FD " << theWccpConnection << ".");

    // Sadly WCCP only does IPv4

    struct sockaddr_in router;
    Config.Wccp.router.GetSockAddr(router);
    if (connect(theWccpConnection, (struct sockaddr*)&router, sizeof(router)))
        fatal("Unable to connect WCCP out socket");

    struct sockaddr_in local;
    memset(&local, '\0', sizeof(local));
    socklen_t slen = sizeof(local);
    if (getsockname(theWccpConnection, (struct sockaddr*)&local, &slen))
        fatal("Unable to getsockname on WCCP out socket");

    local_ip = local;
}