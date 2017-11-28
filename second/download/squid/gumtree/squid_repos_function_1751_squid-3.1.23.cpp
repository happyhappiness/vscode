static void
externalAclRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("external_acl",
                   "External ACL stats",
                   externalAclStats, 0, 1);
}