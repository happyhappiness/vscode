const char *ssl_cmd_SSLStaplingReturnResponderErrors(cmd_parms *cmd,
                                                     void *dcfg, int flag)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->stapling_return_errors = flag ? TRUE : FALSE;
    return NULL;
}