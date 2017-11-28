void
Rock::Rebuild::loadOneSlot()
{
    debugs(47,5, sd->index << " slot " << loadingPos << " at " <<
           dbOffset << " <= " << dbSize);

    ++counts.scancount;

    if (lseek(fd, dbOffset, SEEK_SET) < 0)
        failure("cannot seek to db entry", errno);

    buf.reset();

    if (!storeRebuildLoadEntry(fd, sd->index, buf, counts))
        return;

    const SlotId slotId = loadingPos;

    // get our header
    DbCellHeader header;
    if (buf.contentSize() < static_cast<mb_size_t>(sizeof(header))) {
        debugs(47, DBG_IMPORTANT, "WARNING: cache_dir[" << sd->index << "]: " <<
               "Ignoring truncated " << buf.contentSize() << "-byte " <<
               "cache entry meta data at " << dbOffset);
        freeSlotIfIdle(slotId, true);
        return;
    }
    memcpy(&header, buf.content(), sizeof(header));
    if (header.empty()) {
        freeSlotIfIdle(slotId, false);
        return;
    }
    if (!header.sane(dbSlotSize, dbSlotLimit)) {
        debugs(47, DBG_IMPORTANT, "WARNING: cache_dir[" << sd->index << "]: " <<
               "Ignoring malformed cache entry meta data at " << dbOffset);
        freeSlotIfIdle(slotId, true);
        return;
    }
    buf.consume(sizeof(header)); // optimize to avoid memmove()

    useNewSlot(slotId, header);
}