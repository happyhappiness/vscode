void
peerDigestNeeded(PeerDigest * pd)
{
    assert(pd);
    assert(!pd->flags.needed);
    assert(!pd->cd);

    pd->flags.needed = true;
    pd->times.needed = squid_curtime;
    peerDigestSetCheck(pd, 0);	/* check asap */
}