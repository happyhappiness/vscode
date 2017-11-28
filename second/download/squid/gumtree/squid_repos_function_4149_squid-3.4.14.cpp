void Adaptation::Icap::Xaction::scheduleWrite(MemBuf &buf)
{
    Must(haveConnection());

    // comm module will free the buffer
    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommIoCbParams> Dialer;
    writer = JobCallback(93, 3,
                         Dialer, this, Adaptation::Icap::Xaction::noteCommWrote);

    Comm::Write(connection, &buf, writer);
    updateTimeout();
}