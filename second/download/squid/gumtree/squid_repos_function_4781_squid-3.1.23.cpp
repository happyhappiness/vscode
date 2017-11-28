static void
authenticateRegisterWithCacheManager(authConfig * config)
{
    for (authConfig::iterator i = config->begin(); i != config->end(); ++i) {
        AuthConfig *scheme = *i;
        scheme->registerWithCacheManager();
    }
}