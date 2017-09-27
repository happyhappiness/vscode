static void ssl_dyn_lock_function(int mode, struct CRYPTO_dynlock_value *l,
                           const char *file, int line)
{
    apr_status_t rv;

    if (mode & CRYPTO_LOCK) {
        ap_log_perror(file, line, APLOG_DEBUG, 0, l->pool, 
                      "Acquiring mutex %s:%d", l->file, l->line);
        rv = apr_thread_mutex_lock(l->mutex);
        ap_log_perror(file, line, APLOG_DEBUG, rv, l->pool, 
                      "Mutex %s:%d acquired!", l->file, l->line);
    }
    else {
        ap_log_perror(file, line, APLOG_DEBUG, 0, l->pool, 
                      "Releasing mutex %s:%d", l->file, l->line);
        rv = apr_thread_mutex_unlock(l->mutex);
        ap_log_perror(file, line, APLOG_DEBUG, rv, l->pool, 
                      "Mutex %s:%d released!", l->file, l->line);
    }
}

/*
 * Dynamic lock destruction callback
 */
static void ssl_dyn_destroy_function(struct CRYPTO_dynlock_value *l, 
                          const char *file, int line)
{
    apr_status_t rv;

    ap_log_perror(file, line, APLOG_DEBUG, 0, l->pool, 
                  "Destroying dynamic lock %s:%d", l->file, l->line);
    rv = apr_thread_mutex_destroy(l->mutex);
    if (rv != APR_SUCCESS) {
        ap_log_perror(file, line, APLOG_ERR, rv, l->pool, 
                      "Failed to destroy mutex for dynamic lock %s:%d", 
                      l->file, l->line);
    }

    /* Trust that whomever owned the CRYPTO_dynlock_value we were
     * passed has no future use for it...
