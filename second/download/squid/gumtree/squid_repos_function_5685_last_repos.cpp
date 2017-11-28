void
CredentialsCache::doConfigChangeCleanup()
{
    // purge expired entries entirely
    cleanup();
    // purge the ACL match data stored in the credentials
    for (auto i : store_) {
        aclCacheMatchFlush(&i.second->proxy_match_cache);
    }
}