void
DiskThreadsDiskIOModule::shutdown()
{
    DiskThreadsIOStrategy::Instance.done();
}