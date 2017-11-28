void
AuthUser::CachedACLsReset()
{
    /*
     * We walk the hash by username as that is the unique key we use.
     * This must complete all at once, because we are ensuring correctness.
     */
    AuthUserHashPointer *usernamehash;
    AuthUser *auth_user;
    debugs(29, 3, "AuthUser::CachedACLsReset: Flushing the ACL caches for all users.");
    hash_first(proxy_auth_username_cache);

    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        auth_user = usernamehash->user();
        /* free cached acl results */
        aclCacheMatchFlush(&auth_user->proxy_match_cache);

    }

    debugs(29, 3, "AuthUser::CachedACLsReset: Finished.");
}