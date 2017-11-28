static void
peerDigestFetchFinish(DigestFetchState * fetch, int err)
{
    assert(fetch->entry && fetch->request);

    if (fetch->old_entry) {
        debugs(72, 2, "peerDigestFetchFinish: deleting old entry");
        storeUnregister(fetch->old_sc, fetch->old_entry, fetch);
        fetch->old_entry->releaseRequest();
        fetch->old_entry->unlock();
        fetch->old_entry = NULL;
    }

    /* update global stats */
    kb_incr(&statCounter.cd.kbytes_sent, (size_t) fetch->sent.bytes);

    kb_incr(&statCounter.cd.kbytes_recv, (size_t) fetch->recv.bytes);

    statCounter.cd.msgs_sent += fetch->sent.msg;

    statCounter.cd.msgs_recv += fetch->recv.msg;

    /* unlock everything */
    storeUnregister(fetch->sc, fetch->entry, fetch);

    fetch->entry->unlock();

    HTTPMSGUNLOCK(fetch->request);

    fetch->entry = NULL;

    assert(fetch->pd == NULL);

    cbdataFree(fetch);
}