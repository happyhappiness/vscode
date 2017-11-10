const char *ssl_cmd_SSLUseStapling(cmd_parms *cmd, void *dcfg, int flag)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->stapling_enabled = flag ? TRUE : FALSE;
    return NULL;
}