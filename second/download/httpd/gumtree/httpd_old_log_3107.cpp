ap_log_error(APLOG_MARK, APLOG_CRIT, status, s,
                     "Digest: error generating secret: %s",
                     apr_strerror(status, buf, sizeof(buf)));