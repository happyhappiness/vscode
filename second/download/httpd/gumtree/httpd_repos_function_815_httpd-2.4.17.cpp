const char *ssl_cmd_SSLCertificateFile(cmd_parms *cmd,
                                       void *dcfg,
                                       const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_file(cmd, &arg))) {
        return err;
    }

    *(const char **)apr_array_push(sc->server->pks->cert_files) =
        apr_pstrdup(cmd->pool, arg);
    
    return NULL;
}