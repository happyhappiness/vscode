void
DiskDaemonDiskIOModule::registerWithCacheManager(void)
{
    Mgr::RegisterAction("diskd", "DISKD Stats", &DiskdAction::Create, 0, 1);
}