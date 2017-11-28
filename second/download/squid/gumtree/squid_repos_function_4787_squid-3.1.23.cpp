void
AuthUserHashPointer::removeFromCache(void *usernamehash_p)
{
    AuthUserHashPointer *usernamehash = static_cast<AuthUserHashPointer *>(usernamehash_p);
    AuthUser *auth_user = usernamehash->auth_user;

    if ((authenticateAuthUserInuse(auth_user) - 1))
        debugs(29, 1, "AuthUserHashPointer::removeFromCache: entry in use - not freeing");

    auth_user->unlock();

    /** \todo change behaviour - we remove from the auth user list here, and then unlock, and the
     * delete ourselves.
     */
}