    {
        if (APR_BUCKET_IS_EOS(b)) {
            eos = b;
            break;
        }

        rv = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01463) "apr_bucket_read()");
            return rv;
        }

