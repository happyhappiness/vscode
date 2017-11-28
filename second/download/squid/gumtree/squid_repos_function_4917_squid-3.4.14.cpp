StoreIOState::Pointer
Rock::SwapDir::openStoreIO(StoreEntry &e, StoreIOState::STFNCB *cbFile, StoreIOState::STIOCB *cbIo, void *data)
{
    if (!theFile || theFile->error()) {
        debugs(47,4, HERE << theFile);
        return NULL;
    }

    if (e.swap_filen < 0) {
        debugs(47,4, HERE << e);
        return NULL;
    }

    // Do not start I/O transaction if there are less than 10% free pages left.
    // TODO: reserve page instead
    if (needsDiskStrand() &&
            Ipc::Mem::PageLevel(Ipc::Mem::PageId::ioPage) >= 0.9 * Ipc::Mem::PageLimit(Ipc::Mem::PageId::ioPage)) {
        debugs(47, 5, HERE << "too few shared pages for IPC I/O left");
        return NULL;
    }

    // The are two ways an entry can get swap_filen: our get() locked it for
    // reading or our storeSwapOutStart() locked it for writing. Peeking at our
    // locked entry is safe, but no support for reading a filling entry.
    const Ipc::StoreMapSlot *slot = map->peekAtReader(e.swap_filen);
    if (!slot)
        return NULL; // we were writing afterall

    IoState *sio = new IoState(this, &e, cbFile, cbIo, data);

    sio->swap_dirn = index;
    sio->swap_filen = e.swap_filen;
    sio->payloadEnd = sizeof(DbCellHeader) + map->extras(e.swap_filen).payloadSize;
    assert(sio->payloadEnd <= max_objsize); // the payload fits the slot

    debugs(47,5, HERE << "dir " << index << " has old filen: " <<
           std::setfill('0') << std::hex << std::uppercase << std::setw(8) <<
           sio->swap_filen);

    assert(slot->basics.swap_file_sz > 0);
    assert(slot->basics.swap_file_sz == e.swap_file_sz);

    sio->diskOffset = diskOffset(sio->swap_filen);
    assert(sio->diskOffset + sio->payloadEnd <= diskOffsetLimit());

    sio->file(theFile);
    return sio;
}