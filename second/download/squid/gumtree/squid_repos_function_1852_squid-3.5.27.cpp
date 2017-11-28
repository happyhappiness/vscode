static time_t
peerDigestIncDelay(const PeerDigest * pd)
{
    assert(pd);
    return pd->times.retry_delay > 0 ?
           2 * pd->times.retry_delay :  /* exponential backoff */
           PeerDigestReqMinGap; /* minimal delay */
}