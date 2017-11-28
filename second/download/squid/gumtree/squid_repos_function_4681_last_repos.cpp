void write(char *buf, int len) {
        typedef CommCbMemFunT<Server, CommIoCbParams> Dialer;
        writer = JobCallback(33, 5, Dialer, this, Server::clientWriteDone);
        Comm::Write(clientConnection, buf, len, writer, nullptr);
    }