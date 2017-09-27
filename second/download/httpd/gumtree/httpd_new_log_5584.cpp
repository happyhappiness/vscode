ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, APLOGNO(00553)
                "Opening config file %s (%s)",
                name, (status != APR_SUCCESS) ?
                apr_strerror(status, buf, sizeof(buf)) : "successful");