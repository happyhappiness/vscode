void
DiskDaemonDiskIOModule::registerWithCacheManager(void)
{
    CacheManager::GetInstance()->registerAction("diskd", "DISKD Stats", Stats, 0, 1);
}