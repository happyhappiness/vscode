void
Rock::IoState::writeBufToDisk(const SlotId sidNext, const bool eof, const bool lastWrite)
{
    // no slots after the last/eof slot (but partial slots may have a nil next)
    assert(!eof || sidNext < 0);

    // finalize db cell header
    DbCellHeader header;
    memcpy(header.key, e->key, sizeof(header.key));
    header.firstSlot = writeAnchor().start;
    header.nextSlot = sidNext;
    header.payloadSize = theBuf.size - sizeof(DbCellHeader);
    header.entrySize = eof ? offset_ : 0; // storeSwapOutFileClosed sets swap_file_sz after write
    header.version = writeAnchor().basics.timestamp;

    // copy finalized db cell header into buffer
    memcpy(theBuf.mem, &header, sizeof(DbCellHeader));

    // and now allocate another buffer for the WriteRequest so that
    // we can support concurrent WriteRequests (and to ease cleaning)
    // TODO: should we limit the number of outstanding requests?
    size_t wBufCap = 0;
    void *wBuf = memAllocBuf(theBuf.size, &wBufCap);
    memcpy(wBuf, theBuf.mem, theBuf.size);

    const uint64_t diskOffset = dir->diskOffset(sidCurrent);
    debugs(79, 5, HERE << swap_filen << " at " << diskOffset << '+' <<
           theBuf.size);

    WriteRequest *const r = new WriteRequest(
        ::WriteRequest(static_cast<char*>(wBuf), diskOffset, theBuf.size,
                       memFreeBufFunc(wBufCap)), this);
    r->sidCurrent = sidCurrent;
    r->sidNext = sidNext;
    r->eof = lastWrite;

    // theFile->write may call writeCompleted immediatelly
    theFile->write(r);
}