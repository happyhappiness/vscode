void
wccpConnectionOpen(void)
{
    struct addrinfo *router = NULL, *local = NULL;
    debugs(80, 5, "wccpConnectionOpen: Called");

    if (Config.Wccp.router.IsAnyAddr()) {
        debugs(80, 2, "WCCPv1 disabled.");
        return;
    }

    if ( !Config.Wccp.router.SetIPv4() ) {
        debugs(1, 1, "WCCPv1 Disabled. Router " << Config.Wccp.router << " is not IPv4.");
        return;
    }

    if ( !Config.Wccp.address.SetIPv4() ) {
        debugs(1, 1, "WCCPv1 Disabled. Local address " << Config.Wccp.address << " is not IPv4.");
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

    commSetSelect(theWccpConnection,
                  COMM_SELECT_READ,
                  wccpHandleUdp,
                  NULL,
                  0);

    debugs(80, 1, "Accepting WCCPv1 messages on " << Config.Wccp.address << ", FD " << theWccpConnection << ".");

    Config.Wccp.router.GetAddrInfo(router,AF_INET);

    if (connect(theWccpConnection, router->ai_addr, router->ai_addrlen))
        fatal("Unable to connect WCCP out socket");

    Config.Wccp.router.FreeAddrInfo(router);

    Config.Wccp.address.InitAddrInfo(local);

    if (getsockname(theWccpConnection, local->ai_addr, &local->ai_addrlen))
        fatal("Unable to getsockname on WCCP out socket");

    local_ip = *local;

    Config.Wccp.address.FreeAddrInfo(local);
}