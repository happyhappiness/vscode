ap_log_perror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, pool,
                              APLOGNO(02955) "h2_response: invalid header[%d] '%s'",
                              i, (char*)hline);