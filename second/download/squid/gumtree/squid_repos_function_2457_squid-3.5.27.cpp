static void
idnsDoSendQueryVC(nsvc *vc)
{
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