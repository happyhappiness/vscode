            debugs(12, 4, "icpHandleUdp: Ignoring too-small UDP packet");
            break;
        }

        icp_version = (int) buf[1];	/* cheat! */

        if (icp_version == ICP_VERSION_2)
            icpHandleIcpV2(sock, from, buf, len);
        else if (icp_version == ICP_VERSION_3)
            icpHandleIcpV3(sock, from, buf, len);
        else
            debugs(12, 1, "WARNING: Unused ICP version " << icp_version <<
                   " received from " << from);
    }
}

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

/**
 * icpConnectionShutdown only closes the 'in' socket if it is
 * different than the 'out' socket.
 */
void
icpConnectionShutdown(void)
{
    if (theInIcpConnection < 0)
        return;

    if (theInIcpConnection != theOutIcpConnection) {
        debugs(12, 1, "FD " << theInIcpConnection << " Closing ICP connection");
        comm_close(theInIcpConnection);
    }

    /**
     * Here we set 'theInIcpConnection' to -1 even though the ICP 'in'
     * and 'out' sockets might be just one FD.  This prevents this
     * function from executing repeatedly.  When we are really ready to
     * exit or restart, main will comm_close the 'out' descriptor.
     */
    theInIcpConnection = -1;

    /**
     * Normally we only write to the outgoing ICP socket, but
     * we also have a read handler there to catch messages sent
     * to that specific interface.  During shutdown, we must
     * disable reading on the outgoing socket.
     */
    assert(theOutIcpConnection > -1);

    commSetSelect(theOutIcpConnection, COMM_SELECT_READ, NULL, NULL, 0);
}

void
icpConnectionClose(void)
{
    icpConnectionShutdown();

    if (theOutIcpConnection > -1) {
        debugs(12, 1, "FD " << theOutIcpConnection << " Closing ICP connection");
        comm_close(theOutIcpConnection);
        theOutIcpConnection = -1;
    }
}

static void
icpCount(void *buf, int which, size_t len, int delay)
{
    icp_common_t *icp = (icp_common_t *) buf;

    if (len < sizeof(*icp))
        return;

    if (SENT == which) {
        statCounter.icp.pkts_sent++;
        kb_incr(&statCounter.icp.kbytes_sent, len);

        if (ICP_QUERY == icp->opcode) {
            statCounter.icp.queries_sent++;
            kb_incr(&statCounter.icp.q_kbytes_sent, len);
        } else {
            statCounter.icp.replies_sent++;
            kb_incr(&statCounter.icp.r_kbytes_sent, len);
            /* this is the sent-reply service time */
            statHistCount(&statCounter.icp.reply_svc_time, delay);
        }

        if (ICP_HIT == icp->opcode)
            statCounter.icp.hits_sent++;
    } else if (RECV == which) {
        statCounter.icp.pkts_recv++;
        kb_incr(&statCounter.icp.kbytes_recv, len);

        if (ICP_QUERY == icp->opcode) {
            statCounter.icp.queries_recv++;
            kb_incr(&statCounter.icp.q_kbytes_recv, len);
        } else {
            statCounter.icp.replies_recv++;
            kb_incr(&statCounter.icp.r_kbytes_recv, len);
            /* statCounter.icp.query_svc_time set in clientUpdateCounters */
        }

        if (ICP_HIT == icp->opcode)
            statCounter.icp.hits_recv++;
    }
}

#define N_QUERIED_KEYS 8192
#define N_QUERIED_KEYS_MASK 8191
static cache_key queried_keys[N_QUERIED_KEYS][SQUID_MD5_DIGEST_LENGTH];
