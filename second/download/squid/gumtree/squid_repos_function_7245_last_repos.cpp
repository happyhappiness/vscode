bool
Ipc::Mem::GetPage(const PageId::Purpose purpose, PageId &page)
{
    return ThePagePool && PagesAvailable(purpose) > 0 ?
           ThePagePool->get(purpose, page) : false;
}