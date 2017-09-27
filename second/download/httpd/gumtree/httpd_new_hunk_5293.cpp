
    do {
        apr_brigade_cleanup(bb);
        rv = ap_get_brigade(c_i->input_filters, bb, AP_MODE_READBYTES,
                            APR_NONBLOCK_READ, AP_IOBUFSIZE);
        if (rv == APR_SUCCESS) {
            if (c_o->aborted) {
                return APR_EPIPE;
            }
            if (APR_BRIGADE_EMPTY(bb)) {
                break;
            }
#ifdef DEBUGGING
            len = -1;
            apr_brigade_length(bb, 0, &len);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02440)
                          "read %" APR_OFF_T_FMT
                          " bytes from %s", len, name);
