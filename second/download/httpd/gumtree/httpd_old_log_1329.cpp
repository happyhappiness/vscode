ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Certificate Verification: Certificate Chain too long "
                     "(chain has %d certificates, but maximum allowed are "
                     "only %d)",
                     errdepth, depth);