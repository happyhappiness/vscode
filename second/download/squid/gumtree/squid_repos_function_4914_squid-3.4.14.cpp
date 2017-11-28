StoreIOState::Pointer
Rock::SwapDir::createStoreIO(StoreEntry &e, StoreIOState::STFNCB *cbFile, StoreIOState::STIOCB *cbIo, void *data)
{
    if (!theFile || theFile->error()) {
        debugs(47,4, HERE << theFile);
        return NULL;
    }

    // compute payload size for our cell header, using StoreEntry info
    // careful: e.objectLen() may still be negative here
    const int64_t expectedReplySize = e.mem_obj->expectedReplySize();
    assert(expectedReplySize >= 0); // must know to prevent cell overflows
    assert(e.mem_obj->swap_hdr_sz > 0);
    DbCellHeader header;
    header.payloadSize = e.mem_obj->swap_hdr_sz + expectedReplySize;
    const int64_t payloadEnd = sizeof(DbCellHeader) + header.payloadSize;
    assert(payloadEnd <= max_objsize);

    sfileno filen;
    Ipc::StoreMapSlot *const slot =
        map->openForWriting(reinterpret_cast<const cache_key *>(e.key), filen);
    if (!slot) {
        debugs(47, 5, HERE << "map->add failed");
        return NULL;
    }
    e.swap_file_sz = header.payloadSize; // and will be copied to the map
    slot->set(e);
    map->extras(filen) = header;

    // XXX: We rely on our caller, storeSwapOutStart(), to set e.fileno.
    // If that does not happen, the entry will not decrement the read level!

    IoState *sio = new IoState(this, &e, cbFile, cbIo, data);

    sio->swap_dirn = index;
    sio->swap_filen = filen;
    sio->payloadEnd = payloadEnd;
    sio->diskOffset = diskOffset(sio->swap_filen);

    debugs(47,5, HERE << "dir " << index << " created new filen " <<
           std::setfill('0') << std::hex << std::uppercase << std::setw(8) <<
           sio->swap_filen << std::dec << " at " << sio->diskOffset);

    assert(sio->diskOffset + payloadEnd <= diskOffsetLimit());

    sio->file(theFile);

    trackReferences(e);
    return sio;
}