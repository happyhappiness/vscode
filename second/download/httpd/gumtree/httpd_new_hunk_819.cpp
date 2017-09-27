        }
    }

    return OK;
}

int ap_open_logs(apr_pool_t *pconf, apr_pool_t *p /* plog */,
                 apr_pool_t *ptemp, server_rec *s_main)
{
    apr_status_t rc = APR_SUCCESS;
    server_rec *virt, *q;
    int replace_stderr;
    apr_file_t *errfile = NULL;

    apr_pool_cleanup_register(p, NULL, clear_handle_list,
                              apr_pool_cleanup_null);
    if (open_error_log(s_main, p) != OK) {
        return DONE;
    }

    replace_stderr = 1;
    if (s_main->error_log) {
        /* replace stderr with this new log */
        apr_file_flush(s_main->error_log);
        if ((rc = apr_file_open_stderr(&errfile, p)) == APR_SUCCESS) {
            rc = apr_file_dup2(errfile, s_main->error_log, p);
        }
        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rc, s_main,
                         "unable to replace stderr with error_log");
        }
        else {
            replace_stderr = 0;
        }
    }
    /* note that stderr may still need to be replaced with something
     * because it points to the old error log, or back to the tty
     * of the submitter.
     * XXX: This is BS - /dev/null is non-portable
