static void
authenticateRegisterWithCacheManager(Auth::ConfigVector * config)
{
    for (Auth::ConfigVector::iterator i = config->begin(); i != config->end(); ++i) {
        Auth::Config *scheme = *i;
        scheme->registerWithCacheManager();
    }
}