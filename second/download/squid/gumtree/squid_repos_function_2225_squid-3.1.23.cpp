static void
idnsInitVC(int ns)
{
    char buf[MAX_IPSTRLEN];

    nsvc *vc = cbdataAlloc(nsvc);
    assert(ns < nns);
    nameservers[ns].vc = vc;
    vc->ns = ns;

    IpAddress addr;

    if (!Config.Addrs.udp_outgoing.IsNoAddr())
        addr = Config.Addrs.udp_outgoing;
    else
        addr = Config.Addrs.udp_incoming;

    if (nameservers[ns].S.IsIPv4() && !addr.SetIPv4()) {
        debugs(31, DBG_CRITICAL, "ERROR: Cannot contact DNS nameserver " << nameservers[ns].S << " from " << addr);
        addr.SetAnyAddr();
        addr.SetIPv4();
    }

    vc->queue = new MemBuf;

    vc->msg = new MemBuf;

    vc->fd = comm_open(SOCK_STREAM,
                       IPPROTO_TCP,
                       addr,
                       COMM_NONBLOCKING,
                       "DNS TCP Socket");

    if (vc->fd < 0)
        fatal("Could not create a DNS socket");

    comm_add_close_handler(vc->fd, idnsVCClosed, vc);

    vc->busy = 1;

    commConnectStart(vc->fd, nameservers[ns].S.NtoA(buf,MAX_IPSTRLEN), nameservers[ns].S.GetPort(), idnsInitVCConnected, vc);
}