    if (vc->busy)
        return;

    if (vc->queue->contentSize() == 0)
        return;

    MemBuf *mb = vc->queue;

    vc->queue = new MemBuf;

    vc->busy = 1;

    commSetTimeout(vc->fd, Config.Timeout.idns_query, NULL, NULL);

    comm_write_mbuf(vc->fd, mb, idnsSentQueryVC, vc);

    delete mb;
}

static void
idnsInitVCConnected(int fd, const DnsLookupDetails &details, comm_err_t status, int xerrno, void *data)
{
    nsvc * vc = (nsvc *)data;

    if (status != COMM_OK) {
        char buf[MAX_IPSTRLEN] = "";
        if (vc->ns < nns)
            nameservers[vc->ns].S.NtoA(buf,MAX_IPSTRLEN);
        debugs(78, 1, HERE << "Failed to connect to nameserver " << buf << " using TCP: " << details);
        comm_close(fd);
        return;
    }

    comm_read(fd, (char *)&vc->msglen, 2 , idnsReadVCHeader, vc);
    vc->busy = 0;
    idnsDoSendQueryVC(vc);
}

static void
idnsVCClosed(int fd, void *data)
{
    nsvc * vc = (nsvc *)data;
    delete vc->queue;
    delete vc->msg;
    if (vc->ns < nns) // XXX: idnsShutdown may have freed nameservers[]
        nameservers[vc->ns].vc = NULL;
    cbdataFree(vc);
}

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

static void
idnsSendQueryVC(idns_query * q, int ns)
{
    assert(ns < nns);
