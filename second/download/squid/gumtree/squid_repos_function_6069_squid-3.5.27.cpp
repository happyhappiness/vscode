void DiskIOModule::PokeAllModules(void)
{
    AIODiskIOModule::GetInstance();
    BlockingDiskIOModule::GetInstance();
    DiskDaemonDiskIOModule::GetInstance();
    DiskThreadsDiskIOModule::GetInstance();
    IpcIoDiskIOModule::GetInstance();
    MmappedDiskIOModule::GetInstance();
}