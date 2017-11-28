void
SharedMemPagesRr::create()
{
    Must(!owner);
    owner = Ipc::Mem::PagePool::Init(PagePoolId, Ipc::Mem::PageLimit(),
                                     Ipc::Mem::PageSize());
}