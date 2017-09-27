    apr_status_t status;
#ifdef DEBUG
    char buf[120];
#endif

    if (name == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(00552)
               "Internal error: pcfg_openfile() called with NULL filename");
        return APR_EBADF;
    }

    status = apr_file_open(&file, name, APR_READ | APR_BUFFERED,
                           APR_OS_DEFAULT, p);
#ifdef DEBUG
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, APLOGNO(00553)
                "Opening config file %s (%s)",
                name, (status != APR_SUCCESS) ?
                apr_strerror(status, buf, sizeof(buf)) : "successful");
#endif
    if (status != APR_SUCCESS)
        return status;
