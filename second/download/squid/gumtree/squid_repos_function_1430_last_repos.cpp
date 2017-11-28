static void
peerDigestHandleReply(void *data, StoreIOBuffer receivedData)
{
    DigestFetchState *fetch = (DigestFetchState *)data;
    int retsize = -1;
    digest_read_state_t prevstate;
    int newsize;

    assert(fetch->pd && receivedData.data);
    /* The existing code assumes that the received pointer is
     * where we asked the data to be put
     */
    assert(fetch->buf + fetch->bufofs == receivedData.data);

    /* Update the buffer size */
    fetch->bufofs += receivedData.length;

    assert(fetch->bufofs <= SM_PAGE_SIZE);

    /* If we've fetched enough, return */

    if (peerDigestFetchedEnough(fetch, fetch->buf, fetch->bufofs, "peerDigestHandleReply"))
        return;

    /* Call the right function based on the state */
    /* (Those functions will update the state if needed) */

    /* Give us a temporary reference. Some of the calls we make may
     * try to destroy the fetch structure, and we like to know if they
     * do
     */
    CbcPointer<DigestFetchState> tmpLock = fetch;

    /* Repeat this loop until we're out of data OR the state changes */
    /* (So keep going if the state has changed and we still have data */
    do {
        prevstate = fetch->state;

        switch (fetch->state) {

        case DIGEST_READ_REPLY:
            retsize = peerDigestFetchReply(fetch, fetch->buf, fetch->bufofs);
            break;

        case DIGEST_READ_HEADERS:
            retsize = peerDigestSwapInHeaders(fetch, fetch->buf, fetch->bufofs);
            break;

        case DIGEST_READ_CBLOCK:
            retsize = peerDigestSwapInCBlock(fetch, fetch->buf, fetch->bufofs);
            break;

        case DIGEST_READ_MASK:
            retsize = peerDigestSwapInMask(fetch, fetch->buf, fetch->bufofs);
            break;

        case DIGEST_READ_NONE:
            break;

        case DIGEST_READ_DONE:
            return;
            break;

        default:
            fatal("Bad digest transfer mode!\n");
        }

        if (retsize < 0)
            return;

        /*
         * The returned size indicates how much of the buffer was read -
         * so move the remainder of the buffer to the beginning
         * and update the bufofs / bufsize
         */
        newsize = fetch->bufofs - retsize;

        memmove(fetch->buf, fetch->buf + retsize, fetch->bufofs - newsize);

        fetch->bufofs = newsize;

    } while (cbdataReferenceValid(fetch) && prevstate != fetch->state && fetch->bufofs > 0);

    /* Update the copy offset */
    fetch->offset += receivedData.length;

    /* Schedule another copy */
    if (cbdataReferenceValid(fetch)) {
        StoreIOBuffer tempBuffer;
        tempBuffer.offset = fetch->offset;
        tempBuffer.length = SM_PAGE_SIZE - fetch->bufofs;
        tempBuffer.data = fetch->buf + fetch->bufofs;
        storeClientCopy(fetch->sc, fetch->entry, tempBuffer,
                        peerDigestHandleReply, fetch);
    }
}