
    while (1) {

        /* ### What about APR_EOF? */
        rv = apr_file_gets(w, MAX_STRING_LEN - 1, file);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00717)
                          "Premature end of cache headers.");
            return rv;
        }

        /* Delete terminal (CR?)LF */

