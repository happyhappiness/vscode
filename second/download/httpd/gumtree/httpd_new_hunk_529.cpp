        apr_bucket *bucket;

        rv = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, HUGE_STRING_LEN);
       
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "Error reading request entity data");
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        APR_BRIGADE_FOREACH(bucket, bb) {
            const char *data;
            apr_size_t len;

