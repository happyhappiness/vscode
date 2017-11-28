void
Rock::SwapDir::noteFreeMapSlice(const Ipc::StoreMapSliceId sliceId)
{
    Ipc::Mem::PageId pageId;
    pageId.pool = index+1;
    pageId.number = sliceId+1;
    if (waitingForPage) {
        *waitingForPage = pageId;
        waitingForPage = NULL;
    } else {
        freeSlots->push(pageId);
    }
}