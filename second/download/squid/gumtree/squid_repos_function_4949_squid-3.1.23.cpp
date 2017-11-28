static void
authDigestUserShutdown(void)
{
    /** \todo Future work: the auth framework could flush it's cache */
    AuthUserHashPointer *usernamehash;
    AuthUser *auth_user;
    hash_first(proxy_auth_username_cache);

    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        auth_user = usernamehash->user();

        if (strcmp(auth_user->config->type(), "digest") == 0)
            auth_user->unlock();
    }
}