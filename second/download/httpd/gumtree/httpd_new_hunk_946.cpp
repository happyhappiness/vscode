                               APR_OS_DEFAULT, p)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                         "%s: could not open error log file %s.",
                         ap_server_argv0, fname);
            return DONE;
        }
    }

    return OK;
}

int ap_open_logs(apr_pool_t *pconf, apr_pool_t *p /* plog */, 
