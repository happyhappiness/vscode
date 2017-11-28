void
FtpStateData::maybeReadVirginBody()
{
    // too late to read
    if (!Comm::IsConnOpen(data.conn) || fd_table[data.conn->fd].closing())
        return;

    if (data.read_pending)
        return;

    const int read_sz = replyBodySpace(*data.readBuf, 0);

    debugs(11,9, HERE << "FTP may read up to " << read_sz << " bytes");

    if (read_sz < 2)	// see http.cc
        return;

    data.read_pending = true;

    typedef CommCbMemFunT<FtpStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(9, 5,
                                      TimeoutDialer, this, FtpStateData::ftpTimeout);
    commSetConnTimeout(data.conn, Config.Timeout.read, timeoutCall);

    debugs(9,5,HERE << "queueing read on FD " << data.conn->fd);

    typedef CommCbMemFunT<FtpStateData, CommIoCbParams> Dialer;
    entry->delayAwareRead(data.conn, data.readBuf->space(), read_sz,
                          JobCallback(9, 5, Dialer, this, FtpStateData::dataRead));
}