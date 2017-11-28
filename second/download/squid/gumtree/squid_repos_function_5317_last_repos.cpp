void
Ftp::Client::maybeReadVirginBody()
{
    // too late to read
    if (!Comm::IsConnOpen(data.conn) || fd_table[data.conn->fd].closing())
        return;

    if (data.read_pending)
        return;

    initReadBuf();

    const int read_sz = replyBodySpace(*data.readBuf, 0);

    debugs(9, 9, "FTP may read up to " << read_sz << " bytes");

    if (read_sz < 2) // see http.cc
        return;

    data.read_pending = true;

    typedef CommCbMemFunT<Client, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(9, 5,
                                      TimeoutDialer, this, Ftp::Client::timeout);
    commSetConnTimeout(data.conn, Config.Timeout.read, timeoutCall);

    debugs(9,5,"queueing read on FD " << data.conn->fd);

    typedef CommCbMemFunT<Client, CommIoCbParams> Dialer;
    entry->delayAwareRead(data.conn, data.readBuf->space(), read_sz,
                          JobCallback(9, 5, Dialer, this, Ftp::Client::dataRead));
}