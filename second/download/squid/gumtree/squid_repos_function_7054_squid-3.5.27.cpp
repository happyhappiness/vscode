bool
Ipc::Mem::PagePool::get(const PageId::Purpose purpose, PageId &page)
{
    Must(0 <= purpose && purpose < PageId::maxPurpose);
    if (pageIndex->pop(page)) {
        page.purpose = purpose;
        ++theLevels[purpose];
        return true;
    }
    return false;
}