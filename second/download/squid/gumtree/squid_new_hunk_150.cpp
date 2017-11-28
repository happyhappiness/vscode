    if (vc->busy)
        return;

    if (vc->queue->contentSize() == 0)
        return;

    // if retrying after a TC UDP response, our close handler cb may be pending
    if (fd_table[vc->conn->fd].closing())
        return;

    MemBuf *mb = vc->queue;

    vc->queue = new MemBuf;

    vc->busy = 1;

    // Comm needs seconds but idnsCheckQueue() will check the exact timeout
    const int timeout = (Config.Timeout.idns_query % 1000 ?
                         Config.Timeout.idns_query + 1000 : Config.Timeout.idns_query) / 1000;
    AsyncCall::Pointer nil;

    commSetConnTimeout(vc->conn, timeout, nil);

    AsyncCall::Pointer call = commCbCall(78, 5, "idnsSentQueryVC",
                                         CommIoCbPtrFun(&idnsSentQueryVC, vc));
    Comm::Write(vc->conn, mb, call);

    delete mb;
}

static void
idnsInitVCConnected(const Comm::ConnectionPointer &conn, comm_err_t status, int xerrno, void *data)
{
    nsvc * vc = (nsvc *)data;

    if (status != COMM_OK || !conn) {
        char buf[MAX_IPSTRLEN] = "";
        if (vc->ns < nns)
            nameservers[vc->ns].S.NtoA(buf,MAX_IPSTRLEN);
        debugs(78, 1, HERE << "Failed to connect to nameserver " << buf << " using TCP.");
        return;
    }

    vc->conn = conn;

    comm_add_close_handler(conn->fd, idnsVCClosed, vc);
    AsyncCall::Pointer call = commCbCall(5,4, "idnsReadVCHeader",
                                         CommIoCbPtrFun(idnsReadVCHeader, vc));
    comm_read(conn, (char *)&vc->msglen, 2, call);
    vc->busy = 0;
    idnsDoSendQueryVC(vc);
}

static void
idnsVCClosed(const CommCloseCbParams &params)
{
    nsvc * vc = (nsvc *)params.data;
    delete vc->queue;
    delete vc->msg;
    vc->conn = NULL;
    if (vc->ns < nns) // XXX: dnsShutdown may have freed nameservers[]
        nameservers[vc->ns].vc = NULL;
    cbdataFree(vc);
}

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

static void
idnsSendQueryVC(idns_query * q, int ns)
{
    assert(ns < nns);
