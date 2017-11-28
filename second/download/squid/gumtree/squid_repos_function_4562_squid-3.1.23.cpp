void
StoreFScoss::registerWithCacheManager()
{
    CacheManager::GetInstance()->registerAction("coss", "COSS Stats", Stats, 0, 1);
}