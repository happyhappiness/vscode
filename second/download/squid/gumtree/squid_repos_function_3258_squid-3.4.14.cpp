void MemStoreRr::run(const RunnerRegistry &r)
{
    assert(Config.memShared.configured());
    Ipc::Mem::RegisteredRunner::run(r);
}