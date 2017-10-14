ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(01845)
                    "The crypto library '%s' could not be loaded: %s (%s: %d)", conf->library, err->msg, err->reason, err->rc);