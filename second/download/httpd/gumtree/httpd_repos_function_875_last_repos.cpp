const char *ssl_cmd_SSLStaplingResponseTimeSkew(cmd_parms *cmd, void *dcfg,
                                                    const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->stapling_resptime_skew = atoi(arg);
    if (sc->server->stapling_resptime_skew < 0) {
        return "SSLStaplingResponseTimeSkew: invalid argument";
    }
    return NULL;
}