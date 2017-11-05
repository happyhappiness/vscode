const char *ssl_cmd_SSLStaplingResponseMaxAge(cmd_parms *cmd, void *dcfg,
                                                    const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->stapling_resp_maxage = atoi(arg);
    if (sc->server->stapling_resp_maxage < 0) {
        return "SSLstapling_resp_maxage: invalid argument";
    }
    return NULL;
}