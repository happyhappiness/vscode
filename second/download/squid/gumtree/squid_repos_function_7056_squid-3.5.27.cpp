char *
Ipc::Mem::PagePool::pagePointer(const PageId &page)
{
    Must(pageIndex->pageIdIsValid(page));
    return theBuf + pageSize() * (page.number - 1);
}