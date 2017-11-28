void
Server::readSomeData()
{
    if (reading())
        return;

    debugs(33, 4, clientConnection << ": reading request...");

    // we can only read if there is more than 1 byte of space free
    if (Config.maxRequestBufferSize - inBuf.length() < 2)
        return;

    typedef CommCbMemFunT<Server, CommIoCbParams> Dialer;
    reader = JobCallback(33, 5, Dialer, this, Server::doClientRead);
    Comm::Read(clientConnection, reader);
}