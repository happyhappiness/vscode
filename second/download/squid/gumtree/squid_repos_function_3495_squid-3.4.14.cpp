void
ConnStateData::readSomeData()
{
    if (reading())
        return;

    debugs(33, 4, HERE << clientConnection << ": reading request...");

    if (!maybeMakeSpaceAvailable())
        return;

    typedef CommCbMemFunT<ConnStateData, CommIoCbParams> Dialer;
    reader = JobCallback(33, 5, Dialer, this, ConnStateData::clientReadRequest);
    comm_read(clientConnection, in.addressToReadInto(), getAvailableBufferLength(), reader);
}