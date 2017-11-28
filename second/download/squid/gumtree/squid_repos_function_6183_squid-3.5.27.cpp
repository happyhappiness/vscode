DiskIOStrategy*
MmappedDiskIOModule::createStrategy()
{
    return new MmappedIOStrategy();
}