ap_log_error(APLOG_MARK, rv == APR_SUCCESS ? APLOG_DEBUG : APLOG_ERR,
                     rv, ap_server_conf, APLOGNO(02611)
                     "create: apr_shm_create(%s) %s",
                     fname ? fname : "",
                     rv == APR_SUCCESS ? "succeeded" : "failed");