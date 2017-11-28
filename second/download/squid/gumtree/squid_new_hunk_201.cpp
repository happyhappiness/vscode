
static void
htcpRecv(int fd, void *data)
{
    static char buf[8192];
    int len;
    static Ip::Address from;

    /* Receive up to 8191 bytes, leaving room for a null */

    len = comm_udp_recvfrom(fd, buf, sizeof(buf) - 1, 0, from);

    debugs(31, 3, "htcpRecv: FD " << fd << ", " << len << " bytes from " << from );

    if (len)
        ++statCounter.htcp.pkts_recv;

    htcpHandleMsg(buf, len, from);

    Comm::SetSelect(fd, COMM_SELECT_READ, htcpRecv, NULL, 0);
}

/*
 * ======================================================================
 * PUBLIC FUNCTIONS
 * ======================================================================
 */

void
htcpOpenPorts(void)
{
    if (Config.Port.htcp <= 0) {
        debugs(31, DBG_IMPORTANT, "HTCP Disabled.");
        return;
    }

    htcpIncomingConn = new Comm::Connection;
    htcpIncomingConn->local = Config.Addrs.udp_incoming;
    htcpIncomingConn->local.SetPort(Config.Port.htcp);

    if (!Ip::EnableIpv6 && !htcpIncomingConn->local.SetIPv4()) {
        debugs(31, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << htcpIncomingConn->local << " is not an IPv4 address.");
        fatal("HTCP port cannot be opened.");
    }
    /* split-stack for now requires default IPv4-only HTCP */
    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && htcpIncomingConn->local.IsAnyAddr()) {
        htcpIncomingConn->local.SetIPv4();
    }

    AsyncCall::Pointer call = asyncCall(31, 2,
                                        "htcpIncomingConnectionOpened",
                                        Comm::UdpOpenDialer(&htcpIncomingConnectionOpened));

    Ipc::StartListening(SOCK_DGRAM,
                        IPPROTO_UDP,
                        htcpIncomingConn,
                        Ipc::fdnInHtcpSocket, call);

    if (!Config.Addrs.udp_outgoing.IsNoAddr()) {
        htcpOutgoingConn = new Comm::Connection;
        htcpOutgoingConn->local = Config.Addrs.udp_outgoing;
        htcpOutgoingConn->local.SetPort(Config.Port.htcp);

        if (!Ip::EnableIpv6 && !htcpOutgoingConn->local.SetIPv4()) {
            debugs(31, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << htcpOutgoingConn->local << " is not an IPv4 address.");
            fatal("HTCP port cannot be opened.");
        }
        /* split-stack for now requires default IPv4-only HTCP */
        if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && htcpOutgoingConn->local.IsAnyAddr()) {
            htcpOutgoingConn->local.SetIPv4();
        }

        enter_suid();
        comm_open_listener(SOCK_DGRAM, IPPROTO_UDP, htcpOutgoingConn, "Outgoing HTCP Socket");
        leave_suid();

        if (!Comm::IsConnOpen(htcpOutgoingConn))
            fatal("Cannot open Outgoing HTCP Socket");

        Comm::SetSelect(htcpOutgoingConn->fd, COMM_SELECT_READ, htcpRecv, NULL, 0);

        debugs(31, DBG_IMPORTANT, "Sending HTCP messages from " << htcpOutgoingConn->local);
    }

    if (!htcpDetailPool) {
        htcpDetailPool = memPoolCreate("htcpDetail", sizeof(htcpDetail));
    }
}

static void
htcpIncomingConnectionOpened(const Comm::ConnectionPointer &conn, int)
{
    if (!Comm::IsConnOpen(conn))
        fatal("Cannot open HTCP Socket");

    Comm::SetSelect(conn->fd, COMM_SELECT_READ, htcpRecv, NULL, 0);

    debugs(31, DBG_CRITICAL, "Accepting HTCP messages on " << conn->local);

    if (Config.Addrs.udp_outgoing.IsNoAddr()) {
        htcpOutgoingConn = conn;
        debugs(31, DBG_IMPORTANT, "Sending HTCP messages from " << htcpOutgoingConn->local);
    }
}

int
htcpQuery(StoreEntry * e, HttpRequest * req, peer * p)
{
    cache_key *save_key;
    static char pkt[8192];
    ssize_t pktlen;
