static AuthUser *
authBasicAuthUserFindUsername(const char *username)
{
    AuthUserHashPointer *usernamehash;
    debugs(29, 9, HERE << "Looking for user '" << username << "'");

    if (username && (usernamehash = static_cast<AuthUserHashPointer *>(hash_lookup(proxy_auth_username_cache, username)))) {
        while (usernamehash) {
            if ((usernamehash->user()->auth_type == AUTH_BASIC) &&
                    !strcmp(username, (char const *)usernamehash->key))
                return usernamehash->user();

            usernamehash = static_cast<AuthUserHashPointer *>(usernamehash->next);
        }
    }

    return NULL;
}