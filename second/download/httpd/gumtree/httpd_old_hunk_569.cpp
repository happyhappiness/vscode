                        "Parent: Unable to create child stdin pipe.");
        apr_pool_destroy(ptemp);
        return -1;
    }

    /* httpd-2.0/2.2 specific to work around apr_proc_create bugs */
    if (((rv = apr_file_open_stdout(&child_out, p))
            != APR_SUCCESS) ||
        ((rv = apr_procattr_child_out_set(attr, child_out, NULL))
            != APR_SUCCESS)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                     "Parent: Could not set child process stdout");
    }
