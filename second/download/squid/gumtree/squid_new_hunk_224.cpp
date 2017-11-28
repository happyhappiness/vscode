            debugs(12, 4, "icpHandleUdp: Ignoring too-small UDP packet");
            break;
        }

        icp_version = (int) buf[1];	/* cheat! */

        if (icpOutgoingConn->local == from)
            // ignore ICP packets which loop back (multicast usually)
            debugs(12, 4, "icpHandleUdp: Ignoring UDP packet sent by myself");
        else if (icp_version == ICP_VERSION_2)
            icpHandleIcpV2(sock, from, buf, len);
        else if (icp_version == ICP_VERSION_3)
            icpHandleIcpV3(sock, from, buf, len);
        else
            debugs(12, 1, "WARNING: Unused ICP version " << icp_version <<
                   " received from " << from);
    }
}

void
icpOpenPorts(void)
{
    uint16_t port;

    if ((port = Config.Port.icp) <= 0)
        return;

    icpIncomingConn = new Comm::Connection;
    icpIncomingConn->local = Config.Addrs.udp_incoming;
    icpIncomingConn->local.SetPort(port);

    if (!Ip::EnableIpv6 && !icpIncomingConn->local.SetIPv4()) {
        debugs(12, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << icpIncomingConn->local << " is not an IPv4 address.");
        fatal("ICP port cannot be opened.");
    }
    /* split-stack for now requires default IPv4-only ICP */
    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && icpIncomingConn->local.IsAnyAddr()) {
        icpIncomingConn->local.SetIPv4();
    }

    AsyncCall::Pointer call = asyncCall(12, 2,
                                        "icpIncomingConnectionOpened",
                                        Comm::UdpOpenDialer(&icpIncomingConnectionOpened));

    Ipc::StartListening(SOCK_DGRAM,
                        IPPROTO_UDP,
                        icpIncomingConn,
                        Ipc::fdnInIcpSocket, call);

    if ( !Config.Addrs.udp_outgoing.IsNoAddr() ) {
        icpOutgoingConn = new Comm::Connection;
        icpOutgoingConn->local = Config.Addrs.udp_outgoing;
        icpOutgoingConn->local.SetPort(port);

        if (!Ip::EnableIpv6 && !icpOutgoingConn->local.SetIPv4()) {
            debugs(49, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << icpOutgoingConn->local << " is not an IPv4 address.");
            fatal("ICP port cannot be opened.");
        }
        /* split-stack for now requires default IPv4-only ICP */
        if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && icpOutgoingConn->local.IsAnyAddr()) {
            icpOutgoingConn->local.SetIPv4();
        }

        enter_suid();
        comm_open_listener(SOCK_DGRAM, IPPROTO_UDP, icpOutgoingConn, "Outgoing ICP Port");
        leave_suid();

        if (!Comm::IsConnOpen(icpOutgoingConn))
            fatal("Cannot open Outgoing ICP Port");

        debugs(12, DBG_CRITICAL, "Sending ICP messages from " << icpOutgoingConn->local);

        Comm::SetSelect(icpOutgoingConn->fd, COMM_SELECT_READ, icpHandleUdp, NULL, 0);
        fd_note(icpOutgoingConn->fd, "Outgoing ICP socket");
    }
}

static void
icpIncomingConnectionOpened(const Comm::ConnectionPointer &conn, int errNo)
{
    if (!Comm::IsConnOpen(conn))
        fatal("Cannot open ICP Port");

    Comm::SetSelect(conn->fd, COMM_SELECT_READ, icpHandleUdp, NULL, 0);

    for (const wordlist *s = Config.mcast_group_list; s; s = s->next)
        ipcache_nbgethostbyname(s->key, mcastJoinGroups, NULL); // XXX: pass the conn for mcastJoinGroups usage.

    debugs(12, DBG_IMPORTANT, "Accepting ICP messages on " << conn->local);

    fd_note(conn->fd, "Incoming ICP port");

    if (Config.Addrs.udp_outgoing.IsNoAddr()) {
        icpOutgoingConn = conn;
        debugs(12, DBG_IMPORTANT, "Sending ICP messages from " << icpOutgoingConn->local);
    }
}

/**
 * icpConnectionShutdown only closes the 'in' socket if it is
 * different than the 'out' socket.
 */
void
icpConnectionShutdown(void)
{
    if (!Comm::IsConnOpen(icpIncomingConn))
        return;

    debugs(12, DBG_IMPORTANT, "Stop receiving ICP on " << icpIncomingConn->local);

    /** Release the 'in' socket for lazy closure.
     * in and out sockets may be sharing one same FD.
     * This prevents this function from executing repeatedly.
     */
    icpIncomingConn = NULL;

    /**
     * Normally we only write to the outgoing ICP socket, but
     * we also have a read handler there to catch messages sent
     * to that specific interface.  During shutdown, we must
     * disable reading on the outgoing socket.
     */
    assert(Comm::IsConnOpen(icpOutgoingConn));

    Comm::SetSelect(icpOutgoingConn->fd, COMM_SELECT_READ, NULL, NULL, 0);
}

void
icpClosePorts(void)
{
    icpConnectionShutdown();

    if (icpOutgoingConn != NULL) {
        debugs(12, DBG_IMPORTANT, "Stop sending ICP from " << icpOutgoingConn->local);
        icpOutgoingConn = NULL;
    }
}

static void
icpCount(void *buf, int which, size_t len, int delay)
{
    icp_common_t *icp = (icp_common_t *) buf;

    if (len < sizeof(*icp))
        return;

    if (SENT == which) {
        ++statCounter.icp.pkts_sent;
        kb_incr(&statCounter.icp.kbytes_sent, len);

        if (ICP_QUERY == icp->opcode) {
            ++statCounter.icp.queries_sent;
            kb_incr(&statCounter.icp.q_kbytes_sent, len);
        } else {
            ++statCounter.icp.replies_sent;
            kb_incr(&statCounter.icp.r_kbytes_sent, len);
            /* this is the sent-reply service time */
            statCounter.icp.replySvcTime.count(delay);
        }

        if (ICP_HIT == icp->opcode)
            ++statCounter.icp.hits_sent;
    } else if (RECV == which) {
        ++statCounter.icp.pkts_recv;
        kb_incr(&statCounter.icp.kbytes_recv, len);

        if (ICP_QUERY == icp->opcode) {
            ++statCounter.icp.queries_recv;
            kb_incr(&statCounter.icp.q_kbytes_recv, len);
        } else {
            ++statCounter.icp.replies_recv;
            kb_incr(&statCounter.icp.r_kbytes_recv, len);
            /* statCounter.icp.querySvcTime set in clientUpdateCounters */
        }

        if (ICP_HIT == icp->opcode)
            ++statCounter.icp.hits_recv;
    }
}

#define N_QUERIED_KEYS 8192
#define N_QUERIED_KEYS_MASK 8191
static cache_key queried_keys[N_QUERIED_KEYS][SQUID_MD5_DIGEST_LENGTH];
