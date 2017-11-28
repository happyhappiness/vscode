void Adaptation::Icap::Xaction::start()
{
    Adaptation::Initiate::start();

    readBuf.init(SQUID_TCP_SO_RCVBUF, SQUID_TCP_SO_RCVBUF);
    commBuf = (char*)memAllocBuf(SQUID_TCP_SO_RCVBUF, &commBufSize);
    // make sure maximum readBuf space does not exceed commBuf size
    Must(static_cast<size_t>(readBuf.potentialSpaceSize()) <= commBufSize);
}