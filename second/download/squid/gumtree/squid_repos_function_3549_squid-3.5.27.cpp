void
ConnStateData::readSomeData()
{
    if (reading())
        return;

    debugs(33, 4, HERE << clientConnection << ": reading request...");

    // we can only read if there is more than 1 byte of space free
    if (Config.maxRequestBufferSize - in.buf.length() < 2)
        return;

    typedef CommCbMemFunT<ConnStateData, CommIoCbParams> Dialer;
    reader = JobCallback(33, 5, Dialer, this, ConnStateData::clientReadRequest);
    Comm::Read(clientConnection, reader);
}