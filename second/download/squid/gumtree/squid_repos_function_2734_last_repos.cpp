void
MemStore::noteFreeMapSlice(const Ipc::StoreMapSliceId sliceId)
{
    Ipc::Mem::PageId &pageId = extras->items[sliceId].page;
    debugs(20, 9, "slice " << sliceId << " freed " << pageId);
    assert(pageId);
    Ipc::Mem::PageId slotId;
    slotId.pool = SpacePoolId;
    slotId.number = sliceId + 1;
    if (!waitingFor) {
        // must zero pageId before we give slice (and pageId extras!) to others
        Ipc::Mem::PutPage(pageId);
        freeSlots->push(slotId);
    } else {
        *waitingFor.slot = slotId;
        *waitingFor.page = pageId;
        waitingFor.slot = NULL;
        waitingFor.page = NULL;
        pageId = Ipc::Mem::PageId();
    }
}