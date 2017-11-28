void Adaptation::Icap::Xaction::scheduleWrite(MemBuf &buf)
{
    // comm module will free the buffer
    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommIoCbParams> Dialer;
    writer = JobCallback(93,3,
                         Dialer, this, Adaptation::Icap::Xaction::noteCommWrote);

    comm_write_mbuf(connection, &buf, writer);
    updateTimeout();
}