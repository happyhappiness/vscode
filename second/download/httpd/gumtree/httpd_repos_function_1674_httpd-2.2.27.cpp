static apr_status_t brigade_append(apr_bucket_brigade *bbOut, apr_bucket_brigade *bbIn)
{
    while (!APR_BRIGADE_EMPTY(bbIn)) {
        apr_bucket *e = APR_BRIGADE_FIRST(bbIn);
        const char *str;
        apr_size_t len;
        apr_status_t rv;

        rv = apr_bucket_read(e, &str, &len, APR_BLOCK_READ);
        if (rv != APR_SUCCESS) {
            return rv;
        }

        APR_BUCKET_REMOVE(e);
        if (APR_BUCKET_IS_METADATA(e) || len > APR_BUCKET_BUFF_SIZE/4) {
            APR_BRIGADE_INSERT_TAIL(bbOut, e);
        }
        else {
            if (len > 0) {
                rv = apr_brigade_write(bbOut, NULL, NULL, str, len);
                if (rv != APR_SUCCESS) {
                    apr_bucket_destroy(e);
                    return rv;
                }
            }
            apr_bucket_destroy(e);
        }
    }
    return APR_SUCCESS;
}