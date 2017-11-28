sfileno
MemStore::reserveSapForWriting(Ipc::Mem::PageId &page)
{
    Ipc::Mem::PageId slot;
    if (freeSlots->pop(slot)) {
        debugs(20, 5, "got a previously free slot: " << slot);

        if (Ipc::Mem::GetPage(Ipc::Mem::PageId::cachePage, page)) {
            debugs(20, 5, "and got a previously free page: " << page);
            return slot.number - 1;
        } else {
            debugs(20, 3, "but there is no free page, returning " << slot);
            freeSlots->push(slot);
        }
    }

    // catch free slots delivered to noteFreeMapSlice()
    assert(!waitingFor);
    waitingFor.slot = &slot;
    waitingFor.page = &page;
    if (map->purgeOne()) {
        assert(!waitingFor); // noteFreeMapSlice() should have cleared it
        assert(slot.set());
        assert(page.set());
        debugs(20, 5, "got previously busy " << slot << " and " << page);
        return slot.number - 1;
    }
    assert(waitingFor.slot == &slot && waitingFor.page == &page);
    waitingFor.slot = NULL;
    waitingFor.page = NULL;

    debugs(47, 3, "cannot get a slice; entries: " << map->entryCount());
    throw TexcHere("ran out of mem-cache slots");
}