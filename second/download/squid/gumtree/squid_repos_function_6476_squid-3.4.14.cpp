void
Ipc::Mem::PagePool::put(PageId &page)
{
    if (!page)
        return;

    Must(0 <= page.purpose && page.purpose < PageId::maxPurpose);
    --theLevels[page.purpose];
    page.purpose = PageId::maxPurpose;
    return pageIndex->push(page);
}