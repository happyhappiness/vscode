const char *ssl_cmd_SSLCARevocationFile(cmd_parms *cmd,
                                        void *dcfg,
                                        const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_file(cmd, &arg))) {
        return err;
    }

    sc->server->crl_file = arg;

    return NULL;
}