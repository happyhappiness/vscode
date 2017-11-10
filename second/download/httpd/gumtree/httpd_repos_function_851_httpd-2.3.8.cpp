const char *ssl_cmd_SSLStaplingForceURL(cmd_parms *cmd, void *dcfg,
                                        const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->stapling_force_url = arg;
    return NULL;
}