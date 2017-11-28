void
SharedMemPagesRr::open(const RunnerRegistry &)
{
    Must(!ThePagePool);
    ThePagePool = new Ipc::Mem::PagePool(PagePoolId);
}