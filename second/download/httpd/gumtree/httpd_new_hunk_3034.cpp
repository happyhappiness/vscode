
    /* send body */
    if (!r->header_only) {
        apr_bucket *e;
        int finish = FALSE;

        ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, "start body send");

        /* read the body, pass it to the output filters */
        while (ap_get_brigade(data->input_filters,
                              bb,
                              AP_MODE_READBYTES,
                              APR_BLOCK_READ,
                              conf->io_buffer_size) == APR_SUCCESS) {
#if DEBUGGING
            {
                apr_off_t readbytes;
                apr_brigade_length(bb, 0, &readbytes);
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01056)
                             "proxy: readbytes: %#x", readbytes);
            }
#endif
            /* sanity check */
            if (APR_BRIGADE_EMPTY(bb)) {
                apr_brigade_cleanup(bb);
                break;
