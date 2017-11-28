void
authenticateInit(Auth::ConfigVector * config)
{
    /* Do this first to clear memory and remove dead state on a reconfigure */
    if (proxy_auth_username_cache)
        Auth::User::CachedACLsReset();

    /* If we do not have any auth config state to create stop now. */
    if (!config)
        return;

    for (Auth::ConfigVector::iterator i = config->begin(); i != config->end(); ++i) {
        Auth::Config *schemeCfg = *i;

        if (schemeCfg->configured())
            schemeCfg->init(schemeCfg);
    }

    if (!proxy_auth_username_cache)
        Auth::User::cacheInit();

    authenticateRegisterWithCacheManager(config);
}