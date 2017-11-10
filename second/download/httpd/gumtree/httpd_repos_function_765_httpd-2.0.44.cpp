const char *ssl_cmd_SSLProxyCipherSuite(cmd_parms *cmd,
                                        void *dcfg,
                                        const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);

    sc->proxy->auth.cipher_suite = arg;

    return NULL;
}