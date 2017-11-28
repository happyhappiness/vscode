StoreIOState::Pointer
storeCreate(StoreEntry * e, StoreIOState::STFNCB * file_callback, StoreIOState::STIOCB * close_callback, void *callback_data)
{
    assert (e);

    ++store_io_stats.create.calls;

    /*
     * Pick the swapdir
     * We assume that the header has been packed by now ..
     */
    const sdirno dirn = storeDirSelectSwapDir(e);

    if (dirn == -1) {
        debugs(20, 2, "storeCreate: no swapdirs for " << *e);
        ++store_io_stats.create.select_fail;
        return NULL;
    }

    debugs(20, 2, "storeCreate: Selected dir " << dirn << " for " << *e);
    SwapDir *SD = dynamic_cast<SwapDir *>(INDEXSD(dirn));

    /* Now that we have a fs to use, call its storeCreate function */
    StoreIOState::Pointer sio = SD->createStoreIO(*e, file_callback, close_callback, callback_data);

    if (sio == NULL)
        ++store_io_stats.create.create_fail;
    else
        ++store_io_stats.create.success;

    return sio;
}