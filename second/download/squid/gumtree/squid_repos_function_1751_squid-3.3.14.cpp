static void
peerDigestReqFinish(DigestFetchState * fetch, char *buf,
                    int fcb_valid, int pdcb_valid, int pcb_valid,
                    const char *reason, int err)
{
    assert(reason);

    /* must go before peerDigestPDFinish */

    if (pdcb_valid) {
        fetch->pd->flags.requested = 0;
        fetch->pd->req_result = reason;
    }

    /* schedule next check if peer is still out there */
    if (pcb_valid) {
        PeerDigest *pd = fetch->pd;

        if (err) {
            pd->times.retry_delay = peerDigestIncDelay(pd);
            peerDigestSetCheck(pd, pd->times.retry_delay);
        } else {
            pd->times.retry_delay = 0;
            peerDigestSetCheck(pd, peerDigestNewDelay(fetch->entry));
        }
    }

    /* note: order is significant */
    if (fcb_valid)
        peerDigestFetchSetStats(fetch);

    if (pdcb_valid)
        peerDigestPDFinish(fetch, pcb_valid, err);

    if (fcb_valid)
        peerDigestFetchFinish(fetch, err);
}