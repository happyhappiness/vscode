void Adaptation::Icap::Xaction::scheduleRead()
{
    Must(haveConnection());
    Must(!reader);
    Must(readBuf.length() < SQUID_TCP_SO_RCVBUF); // will expand later if needed

    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommIoCbParams> Dialer;
    reader = JobCallback(93, 3, Dialer, this, Adaptation::Icap::Xaction::noteCommRead);
    Comm::Read(connection, reader);
    updateTimeout();
}