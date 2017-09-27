    /* Create a temporary pool for the buffer, and destroy it if something
     * goes wrong so we don't have large buffers of unused memory hanging
     * about for the lifetime of the response.
     */
    apr_pool_create(&sobj->pool, r->pool);

    sobj->buffer = apr_palloc(sobj->pool, dconf->max);
    sobj->buffer_len = dconf->max;

    /* attempt to retrieve the cached entry */
    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_lock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02350)
