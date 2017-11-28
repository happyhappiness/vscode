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


void
wccpConnectionClose(void)
{
