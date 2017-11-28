void
authenticateUserCacheRestart(void)
{
    AuthUserHashPointer *usernamehash;
    AuthUser *auth_user;
    debugs(29, 3, HERE << "Clearing config dependent cache data.");
    hash_first(proxy_auth_username_cache);

    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        auth_user = usernamehash->user();
        debugs(29, 5, "authenticateUserCacheRestat: Clearing cache ACL results for user: " << auth_user->username());
    }
}