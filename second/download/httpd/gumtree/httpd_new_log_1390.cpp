ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "Custom DH parameters (%d bits) for %s loaded from %s",
                     BN_num_bits(dhparams->p), vhost_id,
                     mctx->pks->cert_files[0]);