Auth::User::Pointer
Auth::Config::findUserInCache(const char *nameKey, Auth::Type authType)
{
    AuthUserHashPointer *usernamehash;
    debugs(29, 9, "Looking for user '" << nameKey << "'");

    if (nameKey && (usernamehash = static_cast<AuthUserHashPointer *>(hash_lookup(proxy_auth_username_cache, nameKey)))) {
        while (usernamehash) {
            if ((usernamehash->user()->auth_type == authType) &&
                    !strcmp(nameKey, (char const *)usernamehash->key))
                return usernamehash->user();

            usernamehash = static_cast<AuthUserHashPointer *>(usernamehash->next);
        }
    }

    return NULL;
}