static void ssl_dyn_destroy_function(struct CRYPTO_dynlock_value *l, 
                          const char *file, int line)
{
    apr_status_t rv;

    ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_DEBUG, 0, l->pool,
                  "Destroying dynamic lock %s:%d", l->file, l->line);
    rv = apr_thread_mutex_destroy(l->mutex);
    if (rv != APR_SUCCESS) {
        ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_ERR, rv, l->pool,
                      "Failed to destroy mutex for dynamic lock %s:%d", 
                      l->file, l->line);
    }

    /* Trust that whomever owned the CRYPTO_dynlock_value we were
     * passed has no future use for it...
     */
    apr_pool_destroy(l->pool);
}