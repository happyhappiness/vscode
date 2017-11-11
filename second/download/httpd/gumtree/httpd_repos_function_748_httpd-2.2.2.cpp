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