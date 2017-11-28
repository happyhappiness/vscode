void
SharedMemPagesRr::create(const RunnerRegistry &)
{
    Must(!owner);
    owner = Ipc::Mem::PagePool::Init(PagePoolId, Ipc::Mem::PageLimit(),
                                     Ipc::Mem::PageSize());
}