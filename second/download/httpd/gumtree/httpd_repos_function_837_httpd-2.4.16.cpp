const char *ssl_cmd_SSLProxyProtocol(cmd_parms *cmd,
                                     void *dcfg,
                                     const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);

    sc->proxy->protocol_set = 1;
    return ssl_cmd_protocol_parse(cmd, arg, &sc->proxy->protocol);
}