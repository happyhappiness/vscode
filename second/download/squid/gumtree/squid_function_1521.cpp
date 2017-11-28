int
peerDigestSwapInMask(void *data, char *buf, ssize_t size)
{
    DigestFetchState *fetch = (DigestFetchState *)data;
    PeerDigest *pd;

    pd = fetch->pd;
    assert(pd->cd && pd->cd->mask);

    /*
     * NOTENOTENOTENOTENOTE: buf doesn't point to pd->cd->mask anymore!
     * we need to do the copy ourselves!
     */
    memcpy(pd->cd->mask + fetch->mask_offset, buf, size);

    /* NOTE! buf points to the middle of pd->cd->mask! */

    if (peerDigestFetchedEnough(fetch, NULL, size, "peerDigestSwapInMask"))
        return -1;

    fetch->mask_offset += size;

    if (fetch->mask_offset >= pd->cd->mask_size) {
        debugs(72, 2, "peerDigestSwapInMask: Done! Got " <<
               fetch->mask_offset << ", expected " << pd->cd->mask_size);
        assert(fetch->mask_offset == pd->cd->mask_size);
        assert(peerDigestFetchedEnough(fetch, NULL, 0, "peerDigestSwapInMask"));
        return -1;      /* XXX! */
    } else {
        /* We always read everything, so return so */
        return size;
    }

    fatal("peerDigestSwapInMask(): shouldn't get here!\n");
    return 0; /* keep gcc happy */
}