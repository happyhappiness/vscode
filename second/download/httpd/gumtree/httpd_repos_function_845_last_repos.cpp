const char *ssl_cmd_SSLProtocol(cmd_parms *cmd,
                                void *dcfg,
                                const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);

    sc->server->protocol_set = 1;
    return ssl_cmd_protocol_parse(cmd, arg, &sc->server->protocol);
}