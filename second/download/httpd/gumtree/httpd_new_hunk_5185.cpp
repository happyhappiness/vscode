            apr_shm_remove(fname, gpool);
            rv = apr_shm_create(&shm, size, fname, gpool);
        }
        else {
            rv = apr_shm_create(&shm, size, NULL, gpool);
        }
        ap_log_error(APLOG_MARK, rv == APR_SUCCESS ? APLOG_DEBUG : APLOG_ERR,
                     rv, ap_server_conf, APLOGNO(02611)
                     "create: apr_shm_create(%s) %s",
                     fname ? fname : "",
                     rv == APR_SUCCESS ? "succeeded" : "failed");
        if (rv != APR_SUCCESS) {
            return rv;
        }
        if (fbased) {
            /* Set permissions to shared memory
             * so it can be attached by child process
