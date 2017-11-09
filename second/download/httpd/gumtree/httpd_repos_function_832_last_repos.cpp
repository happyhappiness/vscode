static const char *ssl_cmd_crlcheck_parse(cmd_parms *parms,
                                          const char *arg,
                                          int *mask)
{
    const char *w;

    w = ap_getword_conf(parms->temp_pool, &arg);
    if (strcEQ(w, "none")) {
        *mask = SSL_CRLCHECK_NONE;
    }
    else if (strcEQ(w, "leaf")) {
        *mask = SSL_CRLCHECK_LEAF;
    }
    else if (strcEQ(w, "chain")) {
        *mask = SSL_CRLCHECK_CHAIN;
    }
    else {
        return apr_pstrcat(parms->temp_pool, parms->cmd->name,
                           ": Invalid argument '", w, "'",
                           NULL);
    }

    while (*arg) {
        w = ap_getword_conf(parms->temp_pool, &arg);
        if (strcEQ(w, "no_crl_for_cert_ok")) {
            *mask |= SSL_CRLCHECK_NO_CRL_FOR_CERT_OK;
        }
        else {
            return apr_pstrcat(parms->temp_pool, parms->cmd->name,
                               ": Invalid argument '", w, "'",
                               NULL);
        }
    }

    return NULL;
}