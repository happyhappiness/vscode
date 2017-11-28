static void
idnsInitVC(int ns)
{
    nsvc *vc = cbdataAlloc(nsvc);
    assert(ns < nns);
    assert(vc->conn == NULL); // MUST be NULL from the construction process!
    nameservers[ns].vc = vc;
    vc->ns = ns;
    vc->queue = new MemBuf;
    vc->msg = new MemBuf;
    vc->busy = 1;

    Comm::ConnectionPointer conn = new Comm::Connection();

    if (!Config.Addrs.udp_outgoing.IsNoAddr())
        conn->local = Config.Addrs.udp_outgoing;
    else
        conn->local = Config.Addrs.udp_incoming;

    conn->remote = nameservers[ns].S;

    if (conn->remote.IsIPv4()) {
        conn->local.SetIPv4();
    }

    AsyncCall::Pointer call = commCbCall(78,3, "idnsInitVCConnected", CommConnectCbPtrFun(idnsInitVCConnected, vc));

    Comm::ConnOpener *cs = new Comm::ConnOpener(conn, call, Config.Timeout.connect);
    cs->setHost("DNS TCP Socket");
    AsyncJob::Start(cs);
}