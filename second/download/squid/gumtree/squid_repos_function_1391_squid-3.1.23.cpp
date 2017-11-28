static void
storeSwapOutStart(StoreEntry * e)
{
    MemObject *mem = e->mem_obj;
    StoreIOState::Pointer sio;
    assert(mem);
    /* Build the swap metadata, so the filesystem will know how much
     * metadata there is to store
     */
    debugs(20, 5, "storeSwapOutStart: Begin SwapOut '" << e->url() << "' to dirno " <<
           e->swap_dirn << ", fileno " << std::hex << std::setw(8) << std::setfill('0') <<
           std::uppercase << e->swap_filen);
    e->swap_status = SWAPOUT_WRITING;
    /* If we start swapping out objects with OutOfBand Metadata,
     * then this code needs changing
     */

    /* TODO: make some sort of data,size refcounted immutable buffer
     * and stop fooling ourselves with "const char*" buffers.
     */

    // Create metadata now, possibly in vain: storeCreate needs swap_hdr_sz.
    const char *buf = e->getSerialisedMetaData ();
    assert(buf);

    /* Create the swap file */
    generic_cbdata *c = new generic_cbdata(e);
    sio = storeCreate(e, storeSwapOutFileNotify, storeSwapOutFileClosed, c);

    if (sio == NULL) {
        e->swap_status = SWAPOUT_NONE;
        delete c;
        xfree((char*)buf);
        storeLog(STORE_LOG_SWAPOUTFAIL, e);
        return;
    }

    mem->swapout.sio = sio;
    /* Don't lock until after create, or the replacement
     * code might get confused */

    e->lock();
    /* Pick up the file number if it was assigned immediately */
    e->swap_filen = mem->swapout.sio->swap_filen;

    e->swap_dirn = mem->swapout.sio->swap_dirn;

    /* write out the swap metadata */
    storeIOWrite(mem->swapout.sio, buf, mem->swap_hdr_sz, 0, xfree);
}