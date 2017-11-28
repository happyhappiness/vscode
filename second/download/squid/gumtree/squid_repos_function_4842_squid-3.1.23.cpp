AuthUserRequest *
AuthConfig::CreateAuthUser(const char *proxy_auth)
{
    assert(proxy_auth != NULL);
    debugs(29, 9, "AuthConfig::CreateAuthUser: header = '" << proxy_auth << "'");

    AuthConfig *config = Find(proxy_auth);

    if (config == NULL || !config->active()) {
        debugs(29, 1, "AuthConfig::CreateAuthUser: Unsupported or unconfigured/inactive proxy-auth scheme, '" << proxy_auth << "'");
        return NULL;
    }

    AuthUserRequest *result = config->decode (proxy_auth);

    /*
     * DPW 2007-05-08
     * Do not lock the AuthUserRequest on the caller's behalf.
     * Callers must manage their own locks.
     */
    return result;
}