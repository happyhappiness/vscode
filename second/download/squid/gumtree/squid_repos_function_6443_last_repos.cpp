DiskIOStrategy*
IpcIoDiskIOModule::createStrategy()
{
    return new IpcIoIOStrategy();
}