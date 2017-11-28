StoreIOState::Pointer
Rock::SwapDir::createStoreIO(StoreEntry &e, StoreIOState::STFNCB *cbFile, StoreIOState::STIOCB *cbIo, void *data)
{
    if (!theFile || theFile->error()) {
        debugs(47,4, HERE << theFile);
        return NULL;
    }

    sfileno filen;
    Ipc::StoreMapAnchor *const slot =
        map->openForWriting(reinterpret_cast<const cache_key *>(e.key), filen);
    if (!slot) {
        debugs(47, 5, HERE << "map->add failed");
        return NULL;
    }

    assert(filen >= 0);
    slot->set(e);

    // XXX: We rely on our caller, storeSwapOutStart(), to set e.fileno.
    // If that does not happen, the entry will not decrement the read level!

    Rock::SwapDir::Pointer self(this);
    IoState *sio = new IoState(self, &e, cbFile, cbIo, data);

    sio->swap_dirn = index;
    sio->swap_filen = filen;
    sio->writeableAnchor_ = slot;

    debugs(47,5, HERE << "dir " << index << " created new filen " <<
           std::setfill('0') << std::hex << std::uppercase << std::setw(8) <<
           sio->swap_filen << std::dec << " starting at " <<
           diskOffset(sio->swap_filen));

    sio->file(theFile);

    trackReferences(e);
    return sio;
}