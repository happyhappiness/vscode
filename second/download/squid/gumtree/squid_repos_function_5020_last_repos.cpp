void
Rock::Rebuild::freeSlot(const SlotId slotId, const bool invalid)
{
    debugs(47,5, sd->index << " frees slot " << slotId);
    LoadingSlot slot = loadingSlot(slotId);
    assert(!slot.freed());
    slot.freed(true);

    if (invalid) {
        ++counts.invalid;
        //sd->unlink(fileno); leave garbage on disk, it should not hurt
    }

    Ipc::Mem::PageId pageId;
    pageId.pool = sd->index+1;
    pageId.number = slotId+1;
    sd->freeSlots->push(pageId);
}