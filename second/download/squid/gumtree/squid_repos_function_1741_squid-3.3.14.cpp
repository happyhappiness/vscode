static void
peerDigestCheck(void *data)
{
    PeerDigest *pd = (PeerDigest *)data;
    time_t req_time;

    assert(!pd->flags.requested);

    pd->times.next_check = 0;	/* unknown */

    if (!cbdataReferenceValid(pd->peer)) {
        peerDigestNotePeerGone(pd);
        return;
    }

    debugs(72, 3, "peerDigestCheck: peer " <<  pd->peer->host << ":" << pd->peer->http_port);
    debugs(72, 3, "peerDigestCheck: time: " << squid_curtime <<
           ", last received: " << (long int) pd->times.received << "  (" <<
           std::showpos << (int) (squid_curtime - pd->times.received) << ")");

    /* decide when we should send the request:
     * request now unless too close to other requests */
    req_time = squid_curtime;

    /* per-peer limit */

    if (req_time - pd->times.received < PeerDigestReqMinGap) {
        debugs(72, 2, "peerDigestCheck: " << pd->host <<
               ", avoiding close peer requests (" <<
               (int) (req_time - pd->times.received) << " < " <<
               (int) PeerDigestReqMinGap << " secs).");

        req_time = pd->times.received + PeerDigestReqMinGap;
    }

    /* global limit */
    if (req_time - pd_last_req_time < GlobDigestReqMinGap) {
        debugs(72, 2, "peerDigestCheck: " << pd->host <<
               ", avoiding close requests (" <<
               (int) (req_time - pd_last_req_time) << " < " <<
               (int) GlobDigestReqMinGap << " secs).");

        req_time = pd_last_req_time + GlobDigestReqMinGap;
    }

    if (req_time <= squid_curtime)
        peerDigestRequest(pd);	/* will set pd->flags.requested */
    else
        peerDigestSetCheck(pd, req_time - squid_curtime);
}