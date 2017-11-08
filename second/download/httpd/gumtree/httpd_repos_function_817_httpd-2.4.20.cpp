const char *ssl_cmd_SSLCertificateKeyFile(cmd_parms *cmd,
                                          void *dcfg,
                                          const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_file(cmd, &arg))) {
        return err;
    }

    *(const char **)apr_array_push(sc->server->pks->key_files) = arg;

    return NULL;
}