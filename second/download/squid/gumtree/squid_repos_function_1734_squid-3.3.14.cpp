static void
peerDigestDestroy(PeerDigest * pd)
{
    void *p;
    assert(pd);
    void * peerTmp = pd->peer;

    /*
     * DPW 2007-04-12
     * We locked the peer in peerDigestInit(), this is
     * where we unlock it.  If the peer is still valid,
     * tell it that the digest is gone.
     */
    if (cbdataReferenceValidDone(peerTmp, &p))
        peerNoteDigestGone((CachePeer *)p);

    peerDigestClean(pd);

    delete pd;
}