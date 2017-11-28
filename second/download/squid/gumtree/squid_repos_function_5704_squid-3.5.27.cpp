void
Auth::User::cacheCleanup(void *datanotused)
{
    /*
     * We walk the hash by username as that is the unique key we use.
     * For big hashs we could consider stepping through the cache, 100/200
     * entries at a time. Lets see how it flys first.
     */
    AuthUserHashPointer *usernamehash;
    Auth::User::Pointer auth_user;
    char const *username = NULL;
    debugs(29, 3, HERE << "Cleaning the user cache now");
    debugs(29, 3, HERE << "Current time: " << current_time.tv_sec);
    hash_first(proxy_auth_username_cache);

    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        auth_user = usernamehash->user();
        username = auth_user->username();

        /* if we need to have indedendent expiry clauses, insert a module call
         * here */
        debugs(29, 4, HERE << "Cache entry:\n\tType: " <<
               auth_user->auth_type << "\n\tUsername: " << username <<
               "\n\texpires: " <<
               (long int) (auth_user->expiretime + ::Config.authenticateTTL) <<
               "\n\treferences: " << auth_user->LockCount());

        if (auth_user->expiretime + ::Config.authenticateTTL <= current_time.tv_sec) {
            debugs(29, 5, HERE << "Removing user " << username << " from cache due to timeout.");

            /* Old credentials are always removed. Existing users must hold their own
             * Auth::User::Pointer to the credentials. Cache exists only for finding
             * and re-using current valid credentials.
             */
            hash_remove_link(proxy_auth_username_cache, usernamehash);
            delete usernamehash;
        }
    }

    debugs(29, 3, HERE << "Finished cleaning the user cache.");
    eventAdd("User Cache Maintenance", cacheCleanup, NULL, ::Config.authenticateGCInterval, 1);
    last_discard = squid_curtime;
}