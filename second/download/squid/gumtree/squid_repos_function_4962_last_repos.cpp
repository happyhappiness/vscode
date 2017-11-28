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
    // locked entry is safe, but no support for reading the entry we swap out.
    const Ipc::StoreMapAnchor *slot = map->peekAtReader(e.swap_filen);
    if (!slot)
        return NULL; // we were writing afterall

    Rock::SwapDir::Pointer self(this);
    IoState *sio = new IoState(self, &e, cbFile, cbIo, data);

    sio->swap_dirn = index;
    sio->swap_filen = e.swap_filen;
    sio->readableAnchor_ = slot;
    sio->file(theFile);

    debugs(47,5, HERE << "dir " << index << " has old filen: " <<
           std::setfill('0') << std::hex << std::uppercase << std::setw(8) <<
           sio->swap_filen);

    assert(slot->sameKey(static_cast<const cache_key*>(e.key)));
    // For collapsed disk hits: e.swap_file_sz and slot->basics.swap_file_sz
    // may still be zero and basics.swap_file_sz may grow.
    assert(slot->basics.swap_file_sz >= e.swap_file_sz);

    return sio;
}