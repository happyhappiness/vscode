
    /* send body */
    if (!r->header_only) {
        apr_bucket *e;
        int finish = FALSE;

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: start body send");

        /* read the body, pass it to the output filters */
        while (ap_get_brigade(data->input_filters,
                              bb,
                              AP_MODE_READBYTES,
