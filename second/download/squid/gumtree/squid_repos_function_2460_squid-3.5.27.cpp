static void
idnsInitVC(int nsv)
{
    nsvc *vc = cbdataAlloc(nsvc);
    assert(nsv < nns);
    assert(vc->conn == NULL); // MUST be NULL from the construction process!
    nameservers[nsv].vc = vc;
    vc->ns = nsv;
    vc->queue = new MemBuf;
    vc->msg = new MemBuf;
    vc->busy = 1;

    Comm::ConnectionPointer conn = new Comm::Connection();

    if (!Config.Addrs.udp_outgoing.isNoAddr())
        conn->setAddrs(Config.Addrs.udp_outgoing, nameservers[nsv].S);
    else
        conn->setAddrs(Config.Addrs.udp_incoming, nameservers[nsv].S);

    if (conn->remote.isIPv4())
        conn->local.setIPv4();

    AsyncCall::Pointer call = commCbCall(78,3, "idnsInitVCConnected", CommConnectCbPtrFun(idnsInitVCConnected, vc));

    Comm::ConnOpener *cs = new Comm::ConnOpener(conn, call, Config.Timeout.connect);
    cs->setHost("DNS TCP Socket");
    AsyncJob::Start(cs);
}