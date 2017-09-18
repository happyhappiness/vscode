    int rc;

    rc = log_child(p, program, &dummy);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                     "Couldn't start piped log process");
        return NULL;
    }

    pl = apr_palloc(p, sizeof (*pl));
    pl->p = p;
    ap_piped_log_read_fd(pl) = NULL;
    ap_piped_log_write_fd(pl) = dummy;
