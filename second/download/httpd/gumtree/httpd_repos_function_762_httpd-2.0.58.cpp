const char *ssl_cmd_SSLProxyCARevocationPath(cmd_parms *cmd,
                                             void *dcfg,
                                             const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_dir(cmd, &arg))) {
        return err;
    }

    sc->proxy->crl_path = arg;

    return NULL;
}