const char *ssl_cmd_SSLCARevocationCheck(cmd_parms *cmd,
                                         void *dcfg,
                                         const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);

    return ssl_cmd_crlcheck_parse(cmd, arg, &sc->server->crl_check_mask);
}