static void
peerDigestClean(PeerDigest * pd)
{
    assert(pd);

    if (pd->cd)
        cacheDigestDestroy(pd->cd);

    pd->host.clean();
}