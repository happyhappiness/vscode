    }
    do {
        apr_bucket *bucket;

        rv = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, HUGE_STRING_LEN);

        if (rv != APR_SUCCESS) {
            return rv;
        }

        for (bucket = APR_BRIGADE_FIRST(bb);
             bucket != APR_BRIGADE_SENTINEL(bb);
             bucket = APR_BUCKET_NEXT(bucket))
        {
            const char *data;
            apr_size_t len;

            if (APR_BUCKET_IS_EOS(bucket)) {
                seen_eos = 1;
                break;
