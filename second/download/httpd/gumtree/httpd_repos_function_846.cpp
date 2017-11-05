const char *ssl_cmd_SSLStaplingStandardCacheTimeout(cmd_parms *cmd, void *dcfg,
                                                    const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->stapling_cache_timeout = atoi(arg);
    if (sc->server->stapling_cache_timeout < 0) {
        return "SSLstapling_cache_timeout: invalid argument";
    }
    return NULL;
}