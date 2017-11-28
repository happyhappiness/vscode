void
Auth::Digest::Scheme::PurgeCredentialsCache(void)
{
    AuthUserHashPointer *usernamehash;

    debugs(29, 2, HERE << "Erasing Digest authentication credentials from username cache.");
    hash_first(proxy_auth_username_cache);

    while ((usernamehash = static_cast<AuthUserHashPointer *>(hash_next(proxy_auth_username_cache)) )) {
        Auth::User::Pointer auth_user = usernamehash->user();

        if (strcmp(auth_user->config->type(), "digest") == 0) {
            hash_remove_link(proxy_auth_username_cache, static_cast<hash_link*>(usernamehash));
            delete usernamehash;
        }
    }
}