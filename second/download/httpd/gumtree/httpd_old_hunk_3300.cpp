    piped_log *pl;
    apr_file_t *dummy = NULL;
    int rc;

    rc = log_child(p, program, &dummy, cmdtype, 0);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                     "Couldn't start piped log process '%s'.",
                     (program == NULL) ? "NULL" : program);
        return NULL;
    }

    pl = apr_palloc(p, sizeof (*pl));
