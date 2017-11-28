char *
Ipc::Mem::PagePointer(const PageId &page)
{
    Must(ThePagePool);
    return ThePagePool->pagePointer(page);
}