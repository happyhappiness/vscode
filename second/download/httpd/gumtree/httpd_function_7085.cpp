static struct CRYPTO_dynlock_value *ssl_dyn_create_function(const char *file,
                                                     int line)
{
    struct CRYPTO_dynlock_value *value;
    apr_pool_t *p;
    apr_status_t rv;

    /*
     * We need a pool to allocate our mutex.  Since we can't clear
     * allocated memory from a pool, create a subpool that we can blow
     * away in the destruction callback.
     */
    rv = apr_pool_create(&p, dynlockpool);
    if (rv != APR_SUCCESS) {
        ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_ERR, rv, dynlockpool,
                      APLOGNO(02183) "Failed to create subpool for dynamic lock");
        return NULL;
    }

    ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_TRACE1, 0, p,
                  "Creating dynamic lock");

    value = (struct CRYPTO_dynlock_value *)apr_palloc(p,
                                                      sizeof(struct CRYPTO_dynlock_value));
    if (!value) {
        ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_ERR, 0, p,
                      APLOGNO(02185) "Failed to allocate dynamic lock structure");
        return NULL;
    }

    value->pool = p;
    /* Keep our own copy of the place from which we were created,
       using our own pool. */
    value->file = apr_pstrdup(p, file);
    value->line = line;
    rv = apr_thread_mutex_create(&(value->mutex), APR_THREAD_MUTEX_DEFAULT,
                                p);
    if (rv != APR_SUCCESS) {
        ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_ERR, rv, p, APLOGNO(02186)
                      "Failed to create thread mutex for dynamic lock");
        apr_pool_destroy(p);
        return NULL;
    }
    return value;
}