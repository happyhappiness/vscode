void
SharedMemPagesRr::run(const RunnerRegistry &r)
{
    if (Ipc::Mem::PageLimit() <= 0)
        return;

    Ipc::Mem::RegisteredRunner::run(r);
}