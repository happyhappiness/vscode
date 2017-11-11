const char *ssl_cmd_SSLProxyProtocol(cmd_parms *cmd,
                                     void *dcfg,
                                     const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);

    return ssl_cmd_protocol_parse(cmd, arg, &sc->proxy->protocol);
}