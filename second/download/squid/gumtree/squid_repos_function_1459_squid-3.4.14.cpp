void
StoreEntry::swapOut()
{
    if (!mem_obj)
        return;

    // this flag may change so we must check even if we are swappingOut
    if (EBIT_TEST(flags, ENTRY_ABORTED)) {
        assert(EBIT_TEST(flags, RELEASE_REQUEST));
        // StoreEntry::abort() already closed the swap out file, if any
        // no trimming: data producer must stop production if ENTRY_ABORTED
        return;
    }

    const bool weAreOrMayBeSwappingOut = swappingOut() || mayStartSwapOut();

    Store::Root().maybeTrimMemory(*this, weAreOrMayBeSwappingOut);

    if (mem_obj->swapout.decision != MemObject::SwapOut::swPossible)
        return; // nothing else to do

    // Aborted entries have STORE_OK, but swapoutPossible rejects them. Thus,
    // store_status == STORE_OK below means we got everything we wanted.

    debugs(20, 7, HERE << "storeSwapOut: mem->inmem_lo = " << mem_obj->inmem_lo);
    debugs(20, 7, HERE << "storeSwapOut: mem->endOffset() = " << mem_obj->endOffset());
    debugs(20, 7, HERE << "storeSwapOut: swapout.queue_offset = " << mem_obj->swapout.queue_offset);

    if (mem_obj->swapout.sio != NULL)
        debugs(20, 7, "storeSwapOut: storeOffset() = " << mem_obj->swapout.sio->offset()  );

    int64_t const lowest_offset = mem_obj->lowestMemReaderOffset();

    debugs(20, 7, HERE << "storeSwapOut: lowest_offset = " << lowest_offset);

#if SIZEOF_OFF_T <= 4

    if (mem_obj->endOffset() > 0x7FFF0000) {
        debugs(20, DBG_CRITICAL, "WARNING: preventing off_t overflow for " << url());
        abort();
        return;
    }

#endif
    if (swap_status == SWAPOUT_WRITING)
        assert(mem_obj->inmem_lo <=  mem_obj->objectBytesOnDisk() );

    // buffered bytes we have not swapped out yet
    const int64_t swapout_maxsize = mem_obj->availableForSwapOut();
    assert(swapout_maxsize >= 0);
    debugs(20, 7, "storeSwapOut: swapout_size = " << swapout_maxsize);

    if (swapout_maxsize == 0) { // swapped everything we got
        if (store_status == STORE_OK) { // got everything we wanted
            assert(mem_obj->object_sz >= 0);
            swapOutFileClose(StoreIOState::wroteAll);
        }
        // else need more data to swap out
        return;
    }

    if (store_status == STORE_PENDING) {
        /* wait for a full block to write */

        if (swapout_maxsize < SM_PAGE_SIZE)
            return;

        /*
         * Wait until we are below the disk FD limit, only if the
         * next server-side read won't be deferred.
         */
        if (storeTooManyDiskFilesOpen() && !checkDeferRead(-1))
            return;
    }

    /* Ok, we have stuff to swap out.  Is there a swapout.sio open? */
    if (swap_status == SWAPOUT_NONE) {
        assert(mem_obj->swapout.sio == NULL);
        assert(mem_obj->inmem_lo == 0);
        storeSwapOutStart(this); // sets SwapOut::swImpossible on failures
    }

    if (mem_obj->swapout.sio == NULL)
        return;

    doPages(this);

    if (mem_obj->swapout.sio == NULL)
        /* oops, we're not swapping out any more */
        return;

    if (store_status == STORE_OK) {
        /*
         * If the state is STORE_OK, then all data must have been given
         * to the filesystem at this point because storeSwapOut() is
         * not going to be called again for this entry.
         */
        assert(mem_obj->object_sz >= 0);
        assert(mem_obj->endOffset() == mem_obj->swapout.queue_offset);
        swapOutFileClose(StoreIOState::wroteAll);
    }
}