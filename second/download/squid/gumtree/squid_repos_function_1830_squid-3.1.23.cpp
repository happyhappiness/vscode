StoreIOState::Pointer
storeCreate(StoreEntry * e, StoreIOState::STFNCB * file_callback, StoreIOState::STIOCB * close_callback, void *callback_data)
{
    assert (e);
    ssize_t objsize;
    sdirno dirn;
    RefCount<SwapDir> SD;

    store_io_stats.create.calls++;
    /* This is just done for logging purposes */
    objsize = e->objectLen();

    if (objsize != -1)
        objsize += e->mem_obj->swap_hdr_sz;

    /*
     * Pick the swapdir
     * We assume that the header has been packed by now ..
     */
    dirn = storeDirSelectSwapDir(e);

    if (dirn == -1) {
        debugs(20, 2, "storeCreate: no valid swapdirs for this object");
        store_io_stats.create.select_fail++;
        return NULL;
    }

    debugs(20, 2, "storeCreate: Selected dir '" << dirn << "' for obj size '" << objsize << "'");
    SD = dynamic_cast<SwapDir *>(INDEXSD(dirn));

    /* Now that we have a fs to use, call its storeCreate function */
    StoreIOState::Pointer sio = SD->createStoreIO(*e, file_callback, close_callback, callback_data);

    if (sio == NULL)
        store_io_stats.create.create_fail++;
    else
        store_io_stats.create.success++;

    return sio;
}