void
Ftp::Server::writeEarlyReply(const int code, const char *msg)
{
    debugs(33, 7, code << ' ' << msg);
    assert(99 < code && code < 1000);

    MemBuf mb;
    mb.init();
    mb.appendf("%i %s\r\n", code, msg);

    typedef CommCbMemFunT<Server, CommIoCbParams> Dialer;
    AsyncCall::Pointer call = JobCallback(33, 5, Dialer, this, Ftp::Server::wroteEarlyReply);
    Comm::Write(clientConnection, &mb, call);

    flags.readMore = false;

    // TODO: Create master transaction. Log it in wroteEarlyReply().
}