    return apr_pstrcat(parms->pool, parms->cmd->name,
                       ": directory '", *dir,
                       "' does not exist", NULL);

}

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

const char *ssl_cmd_SSLCertificateKeyFile(cmd_parms *cmd,
                                          void *dcfg,
                                          const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_file(cmd, &arg))) {
        return err;
    }

    *(const char **)apr_array_push(sc->server->pks->key_files) =
        apr_pstrdup(cmd->pool, arg);

    return NULL;
}

const char *ssl_cmd_SSLCertificateChainFile(cmd_parms *cmd,
                                            void *dcfg,
                                            const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    ap_log_error(APLOG_MARK, APLOG_WARNING|APLOG_STARTUP, 0, cmd->server,
                 APLOGNO(02559)
                 "The SSLCertificateChainFile directive (%s:%d) is deprecated, "
                 "SSLCertificateFile should be used instead",
                 cmd->directive->filename, cmd->directive->line_num);

    if ((err = ssl_cmd_check_file(cmd, &arg))) {
        return err;
    }

    sc->server->cert_chain = arg;

    return NULL;
}

#ifdef HAVE_TLS_SESSION_TICKETS
const char *ssl_cmd_SSLSessionTicketKeyFile(cmd_parms *cmd,
