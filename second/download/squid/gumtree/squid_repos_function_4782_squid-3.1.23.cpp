void
authenticateInit(authConfig * config)
{
    for (authConfig::iterator i = config->begin(); i != config->end(); ++i) {
        AuthConfig *scheme = *i;

        if (scheme->configured())
            scheme->init(scheme);
    }

    if (!proxy_auth_username_cache)
        AuthUser::cacheInit();
    else
        AuthUser::CachedACLsReset();

    authenticateRegisterWithCacheManager(&Config.authConfiguration);
}