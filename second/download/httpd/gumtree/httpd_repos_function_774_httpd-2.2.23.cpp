const char *ssl_cmd_SSLCACertificateFile(cmd_parms *cmd,
                                         void *dcfg,
                                         const char *arg)
{
    /*SSLDirConfigRec *dc = (SSLDirConfigRec *)dcfg;*/
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_file(cmd, &arg))) {
        return err;
    }

    /* XXX: bring back per-dir */
    sc->server->auth.ca_cert_file = arg;

    return NULL;
}