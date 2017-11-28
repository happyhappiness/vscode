bool Adaptation::Icap::Xaction::mayReadMore() const
{
    return !doneReading() && // will read more data
           readBuf.length() < SQUID_TCP_SO_RCVBUF;  // have space for more data
}