void
MemStoreRr::useConfig()
{
    assert(Config.memShared.configured());
    Ipc::Mem::RegisteredRunner::useConfig();
}