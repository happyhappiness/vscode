Ipc::Mem::PageId
MemStore::pageForSlice(Ipc::StoreMapSliceId sliceId)
{
    Must(extras);
    Must(sliceId >= 0);
    Ipc::Mem::PageId page = extras->items[sliceId].page;
    Must(page);
    return page;
}