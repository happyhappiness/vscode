static void
externalAclRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("external_acl",
                        "External ACL stats",
                        externalAclStats, 0, 1);
}