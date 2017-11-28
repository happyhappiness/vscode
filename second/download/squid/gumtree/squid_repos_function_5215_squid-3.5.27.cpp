void
Rock::IoState::writeToDisk(const SlotId sidNext)
{
    assert(theFile != NULL);
    assert(theBuf.size >= sizeof(DbCellHeader));

    // TODO: if DiskIO module is mmap-based, we should be writing whole pages
    // to avoid triggering read-page;new_head+old_tail;write-page overheads

    writeBufToDisk(sidNext, sidNext < 0);
    theBuf.clear();

    sidCurrent = sidNext;
}