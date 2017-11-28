void
StoreFileSystem::RegisterAllFsWithCacheManager(void)
{
    for (iterator i = GetFileSystems().begin(); i != GetFileSystems().end(); ++i)
        (*i)->registerWithCacheManager();
}