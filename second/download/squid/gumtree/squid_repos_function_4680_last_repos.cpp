void write(MemBuf *mb) {
        typedef CommCbMemFunT<Server, CommIoCbParams> Dialer;
        writer = JobCallback(33, 5, Dialer, this, Server::clientWriteDone);
        Comm::Write(clientConnection, mb, writer);
    }