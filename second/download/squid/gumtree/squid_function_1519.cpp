int
peerDigestSwapInHeaders(void *data, char *buf, ssize_t size)
{
    DigestFetchState *fetch = (DigestFetchState *)data;
    size_t hdr_size;

    assert(fetch->state == DIGEST_READ_HEADERS);

    if (peerDigestFetchedEnough(fetch, buf, size, "peerDigestSwapInHeaders"))
        return -1;

    assert(!fetch->offset);

    if ((hdr_size = headersEnd(buf, size))) {
        assert(fetch->entry->getReply());
        assert(fetch->entry->getReply()->sline.status() != Http::scNone);

        if (fetch->entry->getReply()->sline.status() != Http::scOkay) {
            debugs(72, DBG_IMPORTANT, "peerDigestSwapInHeaders: " << fetch->pd->host <<
                   " status " << fetch->entry->getReply()->sline.status() <<
                   " got cached!");

            peerDigestFetchAbort(fetch, buf, "internal status error");
            return -1;
        }

        fetch->state = DIGEST_READ_CBLOCK;
        return hdr_size;    /* Say how much data we read */
    } else {
        /* need more data, do we have space? */

        if (size >= SM_PAGE_SIZE) {
            peerDigestFetchAbort(fetch, buf, "stored header too big");
            return -1;
        } else {
            return 0;       /* We need to read more to parse .. */
        }
    }

    fatal("peerDigestSwapInHeaders() - shouldn't get here!\n");
    return 0; /* keep gcc happy */
}