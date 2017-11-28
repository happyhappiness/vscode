int
peerDigestSwapInCBlock(void *data, char *buf, ssize_t size)
{
    DigestFetchState *fetch = (DigestFetchState *)data;

    assert(fetch->state == DIGEST_READ_CBLOCK);

    if (peerDigestFetchedEnough(fetch, buf, size, "peerDigestSwapInCBlock"))
        return -1;

    if (size >= (ssize_t)StoreDigestCBlockSize) {
        PeerDigest *pd = fetch->pd;

        assert(pd && fetch->entry->getReply());

        if (peerDigestSetCBlock(pd, buf)) {
            /* XXX: soon we will have variable header size */
            /* switch to CD buffer and fetch digest guts */
            buf = NULL;
            assert(pd->cd->mask);
            fetch->state = DIGEST_READ_MASK;
            return StoreDigestCBlockSize;
        } else {
            peerDigestFetchAbort(fetch, buf, "invalid digest cblock");
            return -1;
        }
    } else {
        /* need more data, do we have space? */

        if (size >= SM_PAGE_SIZE) {
            peerDigestFetchAbort(fetch, buf, "digest cblock too big");
            return -1;
        } else {
            return 0;		/* We need more data */
        }
    }

    fatal("peerDigestSwapInCBlock(): shouldn't get here!\n");
    return 0; /* keep gcc happy */
}