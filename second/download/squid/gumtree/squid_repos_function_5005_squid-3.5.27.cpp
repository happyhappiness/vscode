void
Ftp::Server::writeReply(MemBuf &mb)
{
    debugs(9, 2, "FTP Client " << clientConnection);
    debugs(9, 2, "FTP Client REPLY:\n---------\n" << mb.buf <<
           "\n----------");

    typedef CommCbMemFunT<Server, CommIoCbParams> Dialer;
    AsyncCall::Pointer call = JobCallback(33, 5, Dialer, this, Ftp::Server::wroteReply);
    Comm::Write(clientConnection, &mb, call);
}