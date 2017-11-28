DiskIOStrategy *
DiskThreadsDiskIOModule::createStrategy()
{
    return new SingletonIOStrategy(&DiskThreadsIOStrategy::Instance);
}