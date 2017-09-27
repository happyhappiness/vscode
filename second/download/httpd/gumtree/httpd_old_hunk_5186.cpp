    return apr_pstrcat(parms->pool, parms->cmd->name,
                       ": directory '", *dir,
                       "' does not exist", NULL);

}

#define SSL_AIDX_CERTS 1
#define SSL_AIDX_KEYS  2

static const char *ssl_cmd_check_aidx_max(cmd_parms *parms,
                                          const char *arg,
                                          int idx)
{
    SSLSrvConfigRec *sc = mySrvConfig(parms->server);
    const char *err, *desc=NULL, **files=NULL;
    int i;

    if ((err = ssl_cmd_check_file(parms, &arg))) {
        return err;
    }

    switch (idx) {
      case SSL_AIDX_CERTS:
        desc = "certificates";
        files = sc->server->pks->cert_files;
        break;
      case SSL_AIDX_KEYS:
        desc = "private keys";
        files = sc->server->pks->key_files;
        break;
    }

    for (i = 0; i < SSL_AIDX_MAX; i++) {
        if (!files[i]) {
            files[i] = arg;
            return NULL;
        }
    }

    return apr_psprintf(parms->pool,
                        "%s: only up to %d "
                        "different %s per virtual host allowed",
                         parms->cmd->name, SSL_AIDX_MAX, desc);
}

const char *ssl_cmd_SSLCertificateFile(cmd_parms *cmd,
                                       void *dcfg,
                                       const char *arg)
{

    const char *err;

    if ((err = ssl_cmd_check_aidx_max(cmd, arg, SSL_AIDX_CERTS))) {
        return err;
    }

    return NULL;
}

const char *ssl_cmd_SSLCertificateKeyFile(cmd_parms *cmd,
                                          void *dcfg,
                                          const char *arg)
{
    const char *err;

    if ((err = ssl_cmd_check_aidx_max(cmd, arg, SSL_AIDX_KEYS))) {
        return err;
    }

    return NULL;
}

const char *ssl_cmd_SSLCertificateChainFile(cmd_parms *cmd,
                                            void *dcfg,
                                            const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_file(cmd, &arg))) {
        return err;
    }

    sc->server->cert_chain = arg;

    return NULL;
}

const char *ssl_cmd_SSLPKCS7CertificateFile(cmd_parms *cmd,
                                            void *dcfg,
                                            const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_file(cmd, &arg))) {
        return err;
    }

    sc->server->pkcs7 = arg;

    return NULL;
}

#ifdef HAVE_TLS_SESSION_TICKETS
const char *ssl_cmd_SSLSessionTicketKeyFile(cmd_parms *cmd,
