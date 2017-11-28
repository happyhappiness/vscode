void
StoreEntry::swapOut()
{
    if (!mem_obj)
        return;

    if (!swapoutPossible())
        return;

    debugs(20, 7, HERE << "storeSwapOut: mem->inmem_lo = " << mem_obj->inmem_lo);
    debugs(20, 7, HERE << "storeSwapOut: mem->endOffset() = " << mem_obj->endOffset());
    debugs(20, 7, HERE << "storeSwapOut: swapout.queue_offset = " << mem_obj->swapout.queue_offset);

    if (mem_obj->swapout.sio != NULL)
        debugs(20, 7, "storeSwapOut: storeOffset() = " << mem_obj->swapout.sio->offset()  );

    int64_t swapout_maxsize = mem_obj->endOffset() - mem_obj->swapout.queue_offset;

    assert(swapout_maxsize >= 0);

    int64_t const lowest_offset = mem_obj->lowestMemReaderOffset();

    debugs(20, 7, HERE << "storeSwapOut: lowest_offset = " << lowest_offset);

    /*
     * Grab the swapout_size and check to see whether we're going to defer
     * the swapout based upon size
     */
    if ((store_status != STORE_OK) && (swapout_maxsize < store_maxobjsize)) {
        /*
         * NOTE: the store_maxobjsize here is the max of optional
         * max-size values from 'cache_dir' lines.  It is not the
         * same as 'maximum_object_size'.  By default, store_maxobjsize
         * will be set to -1.  However, I am worried that this
         * deferance may consume a lot of memory in some cases.
         * It would be good to make this decision based on reply
         * content-length, rather than wait to accumulate huge
         * amounts of object data in memory.
         */
        debugs(20, 5, "storeSwapOut: Deferring starting swapping out");
        return;
    }

    trimMemory();
#if SIZEOF_OFF_T <= 4

    if (mem_obj->endOffset() > 0x7FFF0000) {
        debugs(20, 0, "WARNING: preventing off_t overflow for " << url());
        abort();
        return;
    }

#endif
    if (swap_status == SWAPOUT_WRITING)
        assert(mem_obj->inmem_lo <=  mem_obj->objectBytesOnDisk() );

    if (!swapOutAble())
        return;

    debugs(20, 7, "storeSwapOut: swapout_size = " << swapout_maxsize);

    if (swapout_maxsize == 0) {
        if (store_status == STORE_OK)
            swapOutFileClose();

        return;			/* Nevermore! */
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

        if (checkCachable())
            storeSwapOutStart(this);
        else
            return;

        /* ENTRY_CACHABLE will be cleared and we'll never get here again */
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
        assert(mem_obj->endOffset() == mem_obj->swapout.queue_offset);
        swapOutFileClose();
    }
}