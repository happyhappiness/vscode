static AuthUser *
authDigestUserFindUsername(const char *username)
{
    AuthUserHashPointer *usernamehash;
    AuthUser *auth_user;
    debugs(29, 9, HERE << "Looking for user '" << username << "'");

    if (username && (usernamehash = static_cast < AuthUserHashPointer * >(hash_lookup(proxy_auth_username_cache, username)))) {
        while ((usernamehash->user()->auth_type != AUTH_DIGEST) &&
                (usernamehash->next))
            usernamehash = static_cast < AuthUserHashPointer * >(usernamehash->next);

        auth_user = NULL;

        if (usernamehash->user()->auth_type == AUTH_DIGEST) {
            auth_user = usernamehash->user();
        }

        return auth_user;
    }

    return NULL;
}