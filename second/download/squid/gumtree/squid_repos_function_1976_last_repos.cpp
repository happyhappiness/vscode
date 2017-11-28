void
store_client::doCopy(StoreEntry *anEntry)
{
    assert (anEntry == entry);
    flags.store_copying = true;
    MemObject *mem = entry->mem_obj;

    debugs(33, 5, "store_client::doCopy: co: " <<
           copyInto.offset << ", hi: " <<
           mem->endOffset());

    if (!moreToSend()) {
        /* There is no more to send! */
        debugs(33, 3, HERE << "There is no more to send!");
        callback(0);
        flags.store_copying = false;
        return;
    }

    /* Check that we actually have data */
    if (anEntry->store_status == STORE_PENDING && copyInto.offset >= mem->endOffset()) {
        debugs(90, 3, "store_client::doCopy: Waiting for more");
        flags.store_copying = false;
        return;
    }

    /*
     * Slight weirdness here.  We open a swapin file for any
     * STORE_DISK_CLIENT, even if we can copy the requested chunk
     * from memory in the next block.  We must try to open the
     * swapin file before sending any data to the client side.  If
     * we postpone the open, and then can not open the file later
     * on, the client loses big time.  Its transfer just gets cut
     * off.  Better to open it early (while the client side handler
     * is clientCacheHit) so that we can fall back to a cache miss
     * if needed.
     */

    if (STORE_DISK_CLIENT == getType() && swapin_sio == NULL) {
        if (!startSwapin())
            return; // failure
    }
    scheduleRead();
}