const char *ssl_cmd_SSLStaplingResponderTimeout(cmd_parms *cmd, void *dcfg,
                                                const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->stapling_responder_timeout = atoi(arg);
    sc->server->stapling_responder_timeout *= APR_USEC_PER_SEC;
    if (sc->server->stapling_responder_timeout < 0) {
        return "SSLstapling_responder_timeout: invalid argument";
    }
    return NULL;
}