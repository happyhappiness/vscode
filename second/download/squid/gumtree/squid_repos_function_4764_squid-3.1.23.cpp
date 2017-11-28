void
AuthUser::cacheCleanup(void *datanotused)
{
    /*
     * We walk the hash by username as that is the unique key we use.
     * For big hashs we could consider stepping through the cache, 100/200
     * entries at a time. Lets see how it flys first.
     */
    AuthUserHashPointer *usernamehash;
    AuthUser *auth_user;
    char const *username = NULL;
    debugs(29, 3, "AuthUser::cacheCleanup: Cleaning the user cache now");
    debugs(29, 3, "AuthUser::cacheCleanup: Current time: " << current_time.tv_sec);
    hash_first(proxy_auth_username_cache);

    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        auth_user = usernamehash->user();
        username = auth_user->username();

        /* if we need to have inpedendent expiry clauses, insert a module call
         * here */
        debugs(29, 4, "AuthUser::cacheCleanup: Cache entry:\n\tType: " <<
               auth_user->auth_type << "\n\tUsername: " << username <<
               "\n\texpires: " <<
               (long int) (auth_user->expiretime + Config.authenticateTTL) <<
               "\n\treferences: " << (long int) auth_user->references);

        if (auth_user->expiretime + Config.authenticateTTL <= current_time.tv_sec) {
            debugs(29, 5, "AuthUser::cacheCleanup: Removing user " << username << " from cache due to timeout.");
            /* the minus 1 accounts for the cache lock */

            if (!(authenticateAuthUserInuse(auth_user) - 1))
                /* we don't warn if we leave the user in the cache,
                 * because other modules (ie delay pools) may keep
                 * locks on users, and thats legitimate
                 */
                auth_user->unlock();
        }
    }

    debugs(29, 3, "AuthUser::cacheCleanup: Finished cleaning the user cache.");
    eventAdd("User Cache Maintenance", cacheCleanup, NULL, Config.authenticateGCInterval, 1);
}