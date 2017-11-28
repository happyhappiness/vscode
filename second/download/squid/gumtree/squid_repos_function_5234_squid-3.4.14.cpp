void
authenticateReset(void)
{
    debugs(29, 2, HERE << "Reset authentication State.");

    /* free all username cache entries */
    hash_first(proxy_auth_username_cache);
    AuthUserHashPointer *usernamehash;
    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        debugs(29, 5, HERE << "Clearing entry for user: " << usernamehash->user()->username());
        hash_remove_link(proxy_auth_username_cache, (hash_link *)usernamehash);
        delete usernamehash;
    }

    /* schedule shutdown of the helpers */
    authenticateRotate();

    /* free current global config details too. */
    Auth::TheConfig.clean();
}