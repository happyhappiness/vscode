void
Auth::User::CachedACLsReset()
{
    /*
     * This must complete all at once, because we are ensuring correctness.
     */
    AuthUserHashPointer *usernamehash;
    Auth::User::Pointer auth_user;
    debugs(29, 3, HERE << "Flushing the ACL caches for all users.");
    hash_first(proxy_auth_username_cache);

    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        auth_user = usernamehash->user();
        /* free cached acl results */
        aclCacheMatchFlush(&auth_user->proxy_match_cache);
    }

    debugs(29, 3, HERE << "Finished.");
}