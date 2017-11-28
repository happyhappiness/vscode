static void
peerDigestFetchStop(DigestFetchState * fetch, char *buf, const char *reason)
{
    assert(reason);
    debugs(72, 2, "peerDigestFetchStop: peer " << fetch->pd->host << ", reason: " << reason);
    peerDigestReqFinish(fetch, buf, 1, 1, 1, reason, 0);
}