ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Cannot allocate shared memory: (%d)%s", rv,
                     apr_strerror(rv, buf, sizeof(buf)));