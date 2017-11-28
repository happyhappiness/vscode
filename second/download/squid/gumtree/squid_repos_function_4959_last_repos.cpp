bool
Rock::SwapDir::useFreeSlot(Ipc::Mem::PageId &pageId)
{
    if (freeSlots->pop(pageId)) {
        debugs(47, 5, "got a previously free slot: " << pageId);
        return true;
    }

    // catch free slots delivered to noteFreeMapSlice()
    assert(!waitingForPage);
    waitingForPage = &pageId;
    if (map->purgeOne()) {
        assert(!waitingForPage); // noteFreeMapSlice() should have cleared it
        assert(pageId.set());
        debugs(47, 5, "got a previously busy slot: " << pageId);
        return true;
    }
    assert(waitingForPage == &pageId);
    waitingForPage = NULL;

    debugs(47, 3, "cannot get a slot; entries: " << map->entryCount());
    return false;
}