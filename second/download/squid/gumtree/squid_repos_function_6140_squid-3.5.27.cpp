void
DiskThreadsDiskIOModule::gracefulShutdown()
{
    DiskThreadsIOStrategy::Instance.done();
}