static void
storeSwapOutFileClosed(void *data, int errflag, StoreIOState::Pointer self)
{
    generic_cbdata *c = (generic_cbdata *)data;
    StoreEntry *e = (StoreEntry *)c->data;
    MemObject *mem = e->mem_obj;
    assert(mem->swapout.sio == self);
    assert(e->swap_status == SWAPOUT_WRITING);
    cbdataFree(c);

    if (errflag) {
        debugs(20, 1, "storeSwapOutFileClosed: dirno " << e->swap_dirn << ", swapfile " <<
               std::hex << std::setw(8) << std::setfill('0') << std::uppercase <<
               e->swap_filen << ", errflag=" << errflag);
        debugs(20, 1, "\t" << xstrerror());

        if (errflag == DISK_NO_SPACE_LEFT) {
            /* FIXME: this should be handle by the link from store IO to
             * Store, rather than being a top level API call.
             */
            e->store()->diskFull();
            storeConfigure();
        }

        if (e->swap_filen > 0)
            e->unlink();

        e->swap_filen = -1;

        e->swap_dirn = -1;

        e->swap_status = SWAPOUT_NONE;

        e->releaseRequest();
    } else {
        /* swapping complete */
        debugs(20, 3, "storeSwapOutFileClosed: SwapOut complete: '" << e->url() << "' to " <<
               e->swap_dirn  << ", " << std::hex << std::setw(8) << std::setfill('0') <<
               std::uppercase << e->swap_filen);
        e->swap_file_sz = e->objectLen() + mem->swap_hdr_sz;
        e->swap_status = SWAPOUT_DONE;
        e->store()->updateSize(e->swap_file_sz, 1);

        if (e->checkCachable()) {
            storeLog(STORE_LOG_SWAPOUT, e);
            storeDirSwapLog(e, SWAP_LOG_ADD);
        }

        statCounter.swap.outs++;
    }

    debugs(20, 3, "storeSwapOutFileClosed: " << __FILE__ << ":" << __LINE__);
    mem->swapout.sio = NULL;
    e->unlock();
}