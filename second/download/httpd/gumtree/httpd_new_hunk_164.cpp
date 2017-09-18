        if ((status = apr_file_open(&cls->log_fd, fname, xfer_flags,
                                    xfer_perms, p)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, status, s,
                         "could not open transfer log file %s.", fname);
            exit(1);
        }
        apr_file_inherit_set(cls->log_fd);
    }
#ifdef BUFFERED_LOGS
    cls->outcnt = 0;
#endif

    return cls;
