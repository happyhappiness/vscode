        if (mctx->crl_check_mode == SSL_CRLCHECK_LEAF ||
            mctx->crl_check_mode == SSL_CRLCHECK_CHAIN) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01899)
                         "Host %s: CRL checking has been enabled, but "
                         "neither %sCARevocationFile nor %sCARevocationPath "
                         "is configured", mctx->sc->vhost_id, cfgp, cfgp);
            ssl_die(s);
        }
        return;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01900)
                 "Configuring certificate revocation facility");
