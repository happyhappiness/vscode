        /* fatal error, bail out */
        return result;
    }

    if (apr_file_open(&fd, r->filename, APR_READ, APR_OS_DEFAULT, r->pool) != APR_SUCCESS) {
        /* We can't open it, but we were able to stat it. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    MODNAME ": can't read `%s'", r->filename);
        /* let some other handler decide what the problem is */
        return DECLINED;
    }

    /*
     * try looking at the first HOWMANY bytes
     */
    nbytes = sizeof(buf) - 1;
    if ((result = apr_file_read(fd, (char *) buf, &nbytes)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, result, r,
                    MODNAME ": read failed: %s", r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (nbytes == 0) {
        return DECLINED;
