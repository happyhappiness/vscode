ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf,
                             APLOGNO(02553) "Expected %" APR_SIZE_T_FMT ": Read %" APR_SIZE_T_FMT,
                             size, nbytes);