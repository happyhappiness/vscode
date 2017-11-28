static time_t
peerDigestNewDelay(const StoreEntry * e)
{
    assert(e);

    if (e->expires > 0)
        return e->expires + PeerDigestReqMinGap - squid_curtime;

    return PeerDigestReqMinGap;
}