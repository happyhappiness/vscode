const char *ssl_cmd_SSLOCSPNoVerify(cmd_parms *cmd, void *dcfg, int flag)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);

    sc->server->ocsp_noverify = flag ? TRUE : FALSE;

    return NULL;
}