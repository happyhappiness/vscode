void
ConnStateData::readSomeData()
{
    if (reading())
        return;

    debugs(33, 4, "clientReadSomeData: FD " << fd << ": reading request...");

    if (!maybeMakeSpaceAvailable())
        return;

    typedef CommCbMemFunT<ConnStateData, CommIoCbParams> Dialer;
    reader = JobCallback(33, 5,
                         Dialer, this, ConnStateData::clientReadRequest);
    comm_read(fd, in.addressToReadInto(), getAvailableBufferLength(), reader);
}