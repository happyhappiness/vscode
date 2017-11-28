PeerDigest *
peerDigestCreate(peer * p)
{
    PeerDigest *pd;
    assert(p);

    pd = new PeerDigest;
    peerDigestInit(pd, p);

    /* XXX This does not look right, and the same thing again in the caller */
    return cbdataReference(pd);
}