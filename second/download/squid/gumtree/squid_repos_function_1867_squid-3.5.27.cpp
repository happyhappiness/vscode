static void
peerDigestPDFinish(DigestFetchState * fetch, int pcb_valid, int err)
{
    PeerDigest *pd = fetch->pd;
    const char *host = pd->host.termedBuf();

    pd->times.received = squid_curtime;
    pd->times.req_delay = fetch->resp_time;
    kb_incr(&pd->stats.sent.kbytes, (size_t) fetch->sent.bytes);
    kb_incr(&pd->stats.recv.kbytes, (size_t) fetch->recv.bytes);
    pd->stats.sent.msgs += fetch->sent.msg;
    pd->stats.recv.msgs += fetch->recv.msg;

    if (err) {
        debugs(72, DBG_IMPORTANT, "" << (pcb_valid ? "temporary " : "" ) << "disabling (" << pd->req_result << ") digest from " << host);

        if (pd->cd) {
            cacheDigestDestroy(pd->cd);
            pd->cd = NULL;
        }

        pd->flags.usable = false;

        if (!pcb_valid)
            peerDigestNotePeerGone(pd);
    } else {
        assert(pcb_valid);

        pd->flags.usable = true;

        /* XXX: ugly condition, but how? */

        if (fetch->entry->store_status == STORE_OK)
            debugs(72, 2, "re-used old digest from " << host);
        else
            debugs(72, 2, "received valid digest from " << host);
    }

    cbdataReferenceDone(fetch->pd);
}