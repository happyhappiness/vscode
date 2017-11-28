DiskIOStrategy *
DiskDaemonDiskIOModule::createStrategy()
{
    return new DiskdIOStrategy();
}