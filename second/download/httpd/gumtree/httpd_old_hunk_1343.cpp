        apr_bucket *bucket;

        rv = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, HUGE_STRING_LEN);
       
        if (rv != APR_SUCCESS) {
            return rv;
        }

        APR_BRIGADE_FOREACH(bucket, bb) {
            const char *data;
            apr_size_t len;

