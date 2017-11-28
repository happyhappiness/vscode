static int
peerDigestFetchReply(void *data, char *buf, ssize_t size)
{
    DigestFetchState *fetch = (DigestFetchState *)data;
    PeerDigest *pd = fetch->pd;
    size_t hdr_size;
    assert(pd && buf);
    assert(!fetch->offset);

    assert(fetch->state == DIGEST_READ_REPLY);

    if (peerDigestFetchedEnough(fetch, buf, size, "peerDigestFetchReply"))
        return -1;

    if ((hdr_size = headersEnd(buf, size))) {
        HttpReply const *reply = fetch->entry->getReply();
        assert(reply);
        assert(reply->sline.status() != Http::scNone);
        const Http::StatusCode status = reply->sline.status();
        debugs(72, 3, "peerDigestFetchReply: " << pd->host << " status: " << status <<
               ", expires: " << (long int) reply->expires << " (" << std::showpos <<
               (int) (reply->expires - squid_curtime) << ")");

        /* this "if" is based on clientHandleIMSReply() */

        if (status == Http::scNotModified) {
            /* our old entry is fine */
            assert(fetch->old_entry);

            if (!fetch->old_entry->mem_obj->request) {
                fetch->old_entry->mem_obj->request = fetch->entry->mem_obj->request;
                HTTPMSGLOCK(fetch->old_entry->mem_obj->request);
            }

            assert(fetch->old_entry->mem_obj->request);

            HttpReply *old_rep = (HttpReply *) fetch->old_entry->getReply();

            old_rep->updateOnNotModified(reply);

            fetch->old_entry->timestampsSet();

            /* get rid of 304 reply */
            storeUnregister(fetch->sc, fetch->entry, fetch);

            fetch->entry->unlock();

            fetch->entry = fetch->old_entry;

            fetch->old_entry = NULL;

            /* preserve request -- we need its size to update counters */
            /* requestUnlink(r); */
            /* fetch->entry->mem_obj->request = NULL; */
        } else if (status == Http::scOkay) {
            /* get rid of old entry if any */

            if (fetch->old_entry) {
                debugs(72, 3, "peerDigestFetchReply: got new digest, releasing old one");
                storeUnregister(fetch->old_sc, fetch->old_entry, fetch);
                fetch->old_entry->releaseRequest();
                fetch->old_entry->unlock();
                fetch->old_entry = NULL;
            }
        } else {
            /* some kind of a bug */
            peerDigestFetchAbort(fetch, buf, reply->sline.reason());
            return -1;		/* XXX -1 will abort stuff in ReadReply! */
        }

        /* must have a ready-to-use store entry if we got here */
        /* can we stay with the old in-memory digest? */
        if (status == Http::scNotModified && fetch->pd->cd) {
            peerDigestFetchStop(fetch, buf, "Not modified");
            fetch->state = DIGEST_READ_DONE;
        } else {
            fetch->state = DIGEST_READ_HEADERS;
        }
    } else {
        /* need more data, do we have space? */

        if (size >= SM_PAGE_SIZE)
            peerDigestFetchAbort(fetch, buf, "reply header too big");
    }

    /* We don't want to actually ack that we've handled anything,
     * otherwise SwapInHeaders() won't get the reply line .. */
    return 0;
}