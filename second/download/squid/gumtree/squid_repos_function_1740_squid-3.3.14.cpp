void
peerDigestNotePeerGone(PeerDigest * pd)
{
    if (pd->flags.requested) {
        debugs(72, 2, "peerDigest: peer " << pd->host << " gone, will destroy after fetch.");
        /* do nothing now, the fetching chain will notice and take action */
    } else {
        debugs(72, 2, "peerDigest: peer " << pd->host << " is gone, destroying now.");
        peerDigestDestroy(pd);
    }
}