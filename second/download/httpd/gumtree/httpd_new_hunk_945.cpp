        ap_log_error(APLOG_MARK, APLOG_CRIT, rc, NULL,
                     "unable to replace stderr with error_log");
    }
    return rc;
}

static void log_child_errfn(apr_pool_t *pool, apr_status_t err,
                            const char *description)
{
    ap_log_error(APLOG_MARK, APLOG_ERR, err, NULL,
                 "%s", description);
}

static int log_child(apr_pool_t *p, const char *progname,
                     apr_file_t **fpin)
{
    /* Child process code for 'ErrorLog "|..."';
     * may want a common framework for this, since I expect it will
     * be common for other foo-loggers to want this sort of thing...
