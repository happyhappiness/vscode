void Adaptation::Icap::Xaction::scheduleRead()
{
    Must(connection >= 0);
    Must(!reader);
    Must(readBuf.hasSpace());

    /*
     * See comments in Adaptation::Icap::Xaction.h about why we use commBuf
     * here instead of reading directly into readBuf.buf.
     */
    typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommIoCbParams> Dialer;
    reader = JobCallback(93,3,
                         Dialer, this, Adaptation::Icap::Xaction::noteCommRead);

    comm_read(connection, commBuf, readBuf.spaceSize(), reader);
    updateTimeout();
}