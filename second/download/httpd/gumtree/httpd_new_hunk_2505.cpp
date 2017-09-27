
        /* Need to peek into the file figure out what it really is...
         * ### aught to go back and build a cache for this one of these days.
         */
        if ((rv = apr_file_open(&fh, *cmd, APR_READ | APR_BUFFERED,
                                 APR_OS_DEFAULT, r->pool)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02100)
                          "Failed to open cgi file %s for testing", *cmd);
            return rv;
        }
        if ((rv = apr_file_read(fh, buffer, &bytes)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02101)
                          "Failed to read cgi file %s for testing", *cmd);
            return rv;
        }
        apr_file_close(fh);

        /* Some twisted character [no pun intended] at MS decided that a
