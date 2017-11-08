const char *ssl_cmd_SSLProxyCARevocationFile(cmd_parms *cmd,
                                             void *dcfg,
                                             const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_file(cmd, &arg))) {
        return err;
    }

    sc->proxy->crl_file = arg;

    return NULL;
}