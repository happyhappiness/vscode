ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01824)
                "cipher '%s' not recognised by crypto driver. "
                "session encryption not possible, options: %s", dconf->cipher, options);