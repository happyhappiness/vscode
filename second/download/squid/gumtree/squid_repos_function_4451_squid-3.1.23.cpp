CacheManager*
CacheManager::GetInstance(void)
{
    if (!cm)
        cm=new CacheManager();
    return cm;
}