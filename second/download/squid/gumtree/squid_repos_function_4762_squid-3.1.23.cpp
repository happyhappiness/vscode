void
AuthUser::cacheInit(void)
{
    if (!proxy_auth_username_cache) {
        /* First time around, 7921 should be big enough */
        proxy_auth_username_cache =
            hash_create((HASHCMP *) strcmp, 7921, hash_string);
        assert(proxy_auth_username_cache);
        eventAdd("User Cache Maintenance", cacheCleanup, NULL, Config.authenticateGCInterval, 1);
    }
}