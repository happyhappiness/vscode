        rv = apr_file_open_stderr(&child_err, ptemp);
    }
    if (rv == APR_SUCCESS) {
        if ((rv = apr_procattr_child_err_set(attr, child_err, NULL))
                != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                            "Parent: Unable to connect child stderr.\n");
            apr_pool_destroy(ptemp);
            return -1;
        }
    }

    /* Create the child_ready_event */
