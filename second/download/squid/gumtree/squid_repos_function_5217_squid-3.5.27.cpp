Rock::SlotId
Rock::IoState::reserveSlotForWriting()
{
    Ipc::Mem::PageId pageId;
    if (dir->useFreeSlot(pageId))
        return pageId.number-1;

    // This may happen when the number of available db slots is close to the
    // number of concurrent requests reading or writing those slots, which may
    // happen when the db is "small" compared to the request traffic OR when we
    // are rebuilding and have not loaded "many" entries or empty slots yet.
    throw TexcHere("ran out of free db slots");
}