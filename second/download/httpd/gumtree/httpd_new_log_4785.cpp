ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01899)
                         "Host %s: CRL checking has been enabled, but "
                         "neither %sCARevocationFile nor %sCARevocationPath "
                         "is configured", mctx->sc->vhost_id, cfgp, cfgp);