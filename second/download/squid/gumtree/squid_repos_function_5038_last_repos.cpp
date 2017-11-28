void
Rock::IoState::writeToDisk(const SlotId sidNextProposal)
{
    assert(theFile != NULL);
    assert(theBuf.size >= sizeof(DbCellHeader));

    const bool lastWrite = sidNextProposal < 0;
    const bool eof = lastWrite &&
                     // either not updating or the updating reader has loaded everything
                     (touchingStoreEntry() || staleSplicingPointNext < 0);
    // approve sidNextProposal unless _updating_ the last slot
    const SlotId sidNext = (!touchingStoreEntry() && lastWrite) ?
                           staleSplicingPointNext : sidNextProposal;
    debugs(79, 5, "sidNext:" << sidNextProposal << "=>" << sidNext << " eof=" << eof);

    // TODO: if DiskIO module is mmap-based, we should be writing whole pages
    // to avoid triggering read-page;new_head+old_tail;write-page overheads

    writeBufToDisk(sidNext, eof, lastWrite);
    theBuf.clear();

    sidCurrent = sidNext;
}