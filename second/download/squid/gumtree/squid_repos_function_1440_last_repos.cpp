static void
peerDigestFetchFinish(DigestFetchState * fetch, int err)
{
    assert(fetch->entry && fetch->request);

    if (fetch->old_entry) {
        debugs(72, 3, "peerDigestFetchFinish: deleting old entry");
        storeUnregister(fetch->old_sc, fetch->old_entry, fetch);
        fetch->old_entry->releaseRequest();
        fetch->old_entry->unlock("peerDigestFetchFinish old");
        fetch->old_entry = NULL;
    }

    /* update global stats */
    statCounter.cd.kbytes_sent += fetch->sent.bytes;
    statCounter.cd.kbytes_recv += fetch->recv.bytes;
    statCounter.cd.msgs_sent += fetch->sent.msg;
    statCounter.cd.msgs_recv += fetch->recv.msg;

    delete fetch;
}