
    /* Parse the vary header and dump those fields from the headers_in. */
    /* TODO: Make call to the same thing cache_select calls to crack Vary. */
    if (sobj->headers_in) {
        if (APR_SUCCESS != store_table(sobj->headers_in, sobj->buffer,
                sobj->buffer_len, &slider)) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(02376)
                    "in-headers didn't fit in buffer %s",
                    sobj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return APR_EGENERAL;
        }
