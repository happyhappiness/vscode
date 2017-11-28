void
authenticateInit(Auth::ConfigVector * config)
{
    /* If we do not have any auth config state to create stop now. */
    if (!config)
        return;

    for (Auth::ConfigVector::iterator i = config->begin(); i != config->end(); ++i) {
        Auth::Config *schemeCfg = *i;

        if (schemeCfg->configured())
            schemeCfg->init(schemeCfg);
    }

    authenticateRegisterWithCacheManager(config);
}