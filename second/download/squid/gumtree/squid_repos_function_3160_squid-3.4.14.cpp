void
storeSwapInStart(store_client * sc)
{
    StoreEntry *e = sc->entry;

    if (!EBIT_TEST(e->flags, ENTRY_VALIDATED)) {
        /* We're still reloading and haven't validated this entry yet */
        return;
    }

    if (e->mem_status != NOT_IN_MEMORY)
        debugs(20, 3, HERE << "already IN_MEMORY");

    debugs(20, 3, "storeSwapInStart: called for : " << e->swap_dirn << " " <<
           std::hex << std::setw(8) << std::setfill('0') << std::uppercase <<
           e->swap_filen << " " <<  e->getMD5Text());

    if (e->swap_status != SWAPOUT_WRITING && e->swap_status != SWAPOUT_DONE) {
        debugs(20, DBG_IMPORTANT, "storeSwapInStart: bad swap_status (" << swapStatusStr[e->swap_status] << ")");
        return;
    }

    if (e->swap_filen < 0) {
        debugs(20, DBG_IMPORTANT, "storeSwapInStart: swap_filen < 0");
        return;
    }

    assert(e->mem_obj != NULL);
    debugs(20, 3, "storeSwapInStart: Opening fileno " << std::hex << std::setw(8) << std::setfill('0') << std::uppercase << e->swap_filen);
    sc->swapin_sio = storeOpen(e, storeSwapInFileNotify, storeSwapInFileClosed, sc);
}