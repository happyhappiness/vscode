static void
peerDigestInit(PeerDigest * pd, CachePeer * p)
{
    assert(pd && p);

    memset(pd, 0, sizeof(*pd));
    /*
     * DPW 2007-04-12
     * Lock on to the peer here.  The corresponding cbdataReferenceDone()
     * is in peerDigestDestroy().
     */
    pd->peer = cbdataReference(p);
    /* if peer disappears, we will know it's name */
    pd->host = p->host;

    pd->times.initialized = squid_curtime;
}