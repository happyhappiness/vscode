DiskIOStrategy*
BlockingDiskIOModule::createStrategy()
{
    return new BlockingIOStrategy();
}