        }

        /* read */
        apr_bucket_read(e, &data, &len, APR_BLOCK_READ);

        /* first bucket contains zlib header */
        if (!ctx->inflate_init++) {
            if (len < 10) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01403)
                              "Insufficient data for inflate");
                return APR_EGENERAL;
            }
            else  {
