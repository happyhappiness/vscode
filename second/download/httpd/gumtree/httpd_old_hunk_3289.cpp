        apr_status_t rv;

        /* Replace existing stderr with new log. */
        apr_file_flush(s_main->error_log);
        rv = apr_file_dup2(stderr_log, s_main->error_log, stderr_p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s_main,
                         "unable to replace stderr with error_log");
        }
        else {
            /* We are done with stderr_pool, close it, killing
             * the previous generation's stderr logger
             */
