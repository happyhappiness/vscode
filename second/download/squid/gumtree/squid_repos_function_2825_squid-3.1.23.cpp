void
wccp2ConnectionOpen(void)
{
    struct sockaddr_in router, local, null;
    socklen_t local_len, router_len;

    struct wccp2_service_list_t *service_list_ptr;

    struct wccp2_router_list_t *router_list_ptr;

    debugs(80, 5, "wccp2ConnectionOpen: Called");

    if (wccp2_numrouters == 0 || !wccp2_service_list_head) {
        debugs(80, 2, "WCCPv2 Disabled.");
        return;
    }

    if ( !Config.Wccp2.address.SetIPv4() ) {
        debugs(80, 0, "WCCPv2 Disabled. " << Config.Wccp2.address << " is not an IPv4 address.");
        return;
    }

    Config.Wccp2.address.SetPort(WCCP_PORT);
    theWccp2Connection = comm_open_listener(SOCK_DGRAM,
                                            0,
                                            Config.Wccp2.address,
                                            COMM_NONBLOCKING,
                                            "WCCPv2 Socket");

    if (theWccp2Connection < 0)
        fatal("Cannot open WCCP Port");

#if defined(IP_MTU_DISCOVER) && defined(IP_PMTUDISC_DONT)
    {
        int i = IP_PMTUDISC_DONT;
        setsockopt(theWccp2Connection, SOL_IP, IP_MTU_DISCOVER, &i, sizeof i);
    }

#endif
    commSetSelect(theWccp2Connection,
                  COMM_SELECT_READ,
                  wccp2HandleUdp,
                  NULL,
                  0);

    debugs(80, 1, "Accepting WCCPv2 messages on port " << WCCP_PORT << ", FD " << theWccp2Connection << ".");
    debugs(80, 1, "Initialising all WCCPv2 lists");

    /* Initialise all routers on all services */
    memset(&null, 0, sizeof(null));

    null.sin_family = AF_UNSPEC;

    service_list_ptr = wccp2_service_list_head;

    while (service_list_ptr != NULL) {
        for (router_list_ptr = &service_list_ptr->router_list_head; router_list_ptr->next != NULL; router_list_ptr = router_list_ptr->next) {
            router_len = sizeof(router);
            memset(&router, '\0', router_len);
            router.sin_family = AF_INET;
            router.sin_port = htons(WCCP_PORT);
            router.sin_addr = router_list_ptr->router_sendto_address;

            if (connect(theWccp2Connection, (struct sockaddr *) &router, router_len))
                fatal("Unable to connect WCCP out socket");

            local_len = sizeof(local);

            memset(&local, '\0', local_len);

            if (getsockname(theWccp2Connection, (struct sockaddr *) &local, &local_len))
                fatal("Unable to getsockname on WCCP out socket");

            router_list_ptr->local_ip = local.sin_addr;

            /* Disconnect the sending socket. Note: FreeBSD returns error
             * but disconnects anyway so we have to just assume it worked
             */
            if (wccp2_numrouters > 1)
                connect(theWccp2Connection, (struct sockaddr *) &null, router_len);
        }

        service_list_ptr = service_list_ptr->next;
    }

    wccp2_connected = 1;
}