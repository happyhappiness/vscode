const char *ssl_cmd_SSLEngine(cmd_parms *cmd, void *dcfg, int flag)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);

    sc->enabled = flag ? TRUE : FALSE;

    return NULL;
}