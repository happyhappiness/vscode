static void
storeSwapOutFileClosed(void *data, int errflag, StoreIOState::Pointer self)
{
    StoreEntry *e;
    static_cast<generic_cbdata *>(data)->unwrap(&e);

    MemObject *mem = e->mem_obj;
    assert(mem->swapout.sio == self);
    assert(e->swap_status == SWAPOUT_WRITING);

    // if object_size is still unknown, the entry was probably aborted
    if (errflag || e->objectLen() < 0) {
        debugs(20, 2, "storeSwapOutFileClosed: dirno " << e->swap_dirn << ", swapfile " <<
               std::hex << std::setw(8) << std::setfill('0') << std::uppercase <<
               e->swap_filen << ", errflag=" << errflag);

        if (errflag == DISK_NO_SPACE_LEFT) {
            /* FIXME: this should be handle by the link from store IO to
             * Store, rather than being a top level API call.
             */
            e->store()->diskFull();
            storeConfigure();
        }

        if (e->swap_filen >= 0)
            e->unlink();

        assert(e->swap_status == SWAPOUT_NONE);

        e->releaseRequest();
    } else {
        /* swapping complete */
        debugs(20, 3, "storeSwapOutFileClosed: SwapOut complete: '" << e->url() << "' to " <<
               e->swap_dirn  << ", " << std::hex << std::setw(8) << std::setfill('0') <<
               std::uppercase << e->swap_filen);
        debugs(20, 5, HERE << "swap_file_sz = " <<
               e->objectLen() << " + " << mem->swap_hdr_sz);

        e->swap_file_sz = e->objectLen() + mem->swap_hdr_sz;
        e->swap_status = SWAPOUT_DONE;
        e->store()->swappedOut(*e);

        // XXX: For some Stores, it is pointless to re-check cachability here
        // and it leads to double counts in store_check_cachable_hist. We need
        // another way to signal a completed but failed swapout. Or, better,
        // each Store should handle its own logging and LOG state setting.
        if (e->checkCachable()) {
            storeLog(STORE_LOG_SWAPOUT, e);
            storeDirSwapLog(e, SWAP_LOG_ADD);
        }

        ++statCounter.swap.outs;
    }

    debugs(20, 3, "storeSwapOutFileClosed: " << __FILE__ << ":" << __LINE__);
    mem->swapout.sio = NULL;
    e->unlock("storeSwapOutFileClosed");
}