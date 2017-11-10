const char *ssl_cmd_SSLStaplingErrorCacheTimeout(cmd_parms *cmd, void *dcfg,
                                                 const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->stapling_errcache_timeout = atoi(arg);
    if (sc->server->stapling_errcache_timeout < 0) {
        return "SSLStaplingErrorCacheTimeout: invalid argument";
    }
    return NULL;
}