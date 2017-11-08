const char *ssl_cmd_SSLCADNRequestPath(cmd_parms *cmd, void *dcfg,
                                       const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_dir(cmd, &arg))) {
        return err;
    }

    sc->server->pks->ca_name_path = arg;

    return NULL;
}